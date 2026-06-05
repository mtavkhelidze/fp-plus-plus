# Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.21)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(submodules)
include(vcpkg)
update_submodules()
vcpkg_enable()

project(fp++ VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(clang_tidy)
enable_clang_tidy()

message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
    ${PROJECT_NAME}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/fp DESTINATION include)


enable_testing()
add_subdirectory(test)
