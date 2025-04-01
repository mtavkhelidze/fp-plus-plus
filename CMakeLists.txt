cmake_minimum_required(VERSION 3.30)

# Housekeeping
include(${CMAKE_SOURCE_DIR}/cmake/functions.cmake)
update_submodules()
bootstrap_vcpkg()

set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

project(
    fp++
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

message(STATUS "CMAKE_TOOLCHAIN_FILE: ${VCPKG_TARGET_TRIPLET}")

include_directories(include)
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
subdirs(test)
