cmake_minimum_required(VERSION 3.28)
project(person_bridge_cpp)

find_program(CARGO_BIN cargo)

include(FetchContent)

FetchContent_Declare(
  Corrosion
  GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
  GIT_TAG v0.5)

FetchContent_MakeAvailable(Corrosion)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CARGO_BUILD_TYPE "release")
else()
  set(CARGO_BUILD_TYPE "dev")
endif()

message("build type is ${CARGO_BUILD_TYPE}")

corrosion_import_crate(MANIFEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Cargo.toml
                       PROFILE ${CARGO_BUILD_TYPE})

add_library(${PROJECT_NAME} STATIC src/lib.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE person_bridge_rs)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_dependencies(${PROJECT_NAME} person_bridge_rs)
