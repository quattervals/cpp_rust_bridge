cmake_minimum_required(VERSION 3.28)
project(person-cpp)

find_program(CARGO_BIN cargo)

include(FetchContent)

FetchContent_Declare(
  Corrosion
  GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
  GIT_TAG v0.5.1)

FetchContent_MakeAvailable(Corrosion)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CARGO_BUILD_TYPE "release")
else()
  set(CARGO_BUILD_TYPE "dev")
endif()

set(PERSON_BRIDGE_LIB person_bridge_rs)
set(CXX_BRIDGE_LIB cxx_bridge)

message("Build Type is ${CARGO_BUILD_TYPE}")
message("CC is ${CMAKE_CROSSCOMPILING}")
message("target system ${CMAKE_SYSTEM_NAME}")

find_program(CXXBRIDGE cxxbridge PATHS "$ENV{HOME}/.cargo/bin/")
if(CXXBRIDGE STREQUAL "CXXBRIDGE-NOTFOUND")
  message(
    "Could not find cxxbridge, trying to install with `cargo install cxxbridge-cmd'"
  )
  find_program(CARGO cargo PATHS "$ENV{HOME}/.cargo/bin/")
  if(CARGO STREQUAL "CARGO-NOTFOUND")
    message(
      FATAL_ERROR
        "Requires cargo available in path, install via rustup https://rustup.rs/"
    )
  endif()
  execute_process(COMMAND ${CARGO} install cxxbridge-cmd)
  find_program(CXXBRIDGE cxxbridge PATHS "$ENV{HOME}/.cargo/bin/")
endif()

corrosion_import_crate(MANIFEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Cargo.toml
                       PROFILE ${CARGO_BUILD_TYPE})

corrosion_add_cxxbridge(
  ${CXX_BRIDGE_LIB}
  CRATE
  ${PERSON_BRIDGE_LIB}
  MANIFEST_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}
  FILES
  lib.rs)

add_library(${PROJECT_NAME} STATIC src/lib.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PERSON_BRIDGE_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CXX_BRIDGE_LIB})

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
    ${CMAKE_BINARY_DIR}/crates/${PROJECT_NAME}/corrosion_generated/cxxbridge/${CXX_BRIDGE_LIB}/include/${CXX_BRIDGE_LIB}/
)

add_custom_target(
  ${PROJECT_NAME}-test
  COMMAND cargo test --manifest-path
          ${CMAKE_CURRENT_SOURCE_DIR}/Cargo.toml)
