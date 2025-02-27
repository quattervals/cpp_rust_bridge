cmake_minimum_required(VERSION 3.28)
project(
  consumer
  VERSION 0.1.0
  LANGUAGES CXX C
  DESCRIPTION "C++ <-> Rust Bridge")

if(DEFINED CMAKE_TOOLCHAIN_FILE)
  include(${CMAKE_TOOLCHAIN_FILE})
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/crates/person-cpp)

add_executable(${PROJECT_NAME} use_rust.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE person-cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
