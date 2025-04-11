cmake_minimum_required(VERSION 4.0)

# Housekeeping
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
file(GLOB cmake_files "${CMAKE_SOURCE_DIR}/cmake/*.cmake")
foreach(file ${cmake_files})
    include(${file})
endforeach()

enable_testing()
update_submodules()
enable_vcpkg()

# end of housekeeping

project(
    fp++
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# clang-tidy things
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_clang_tidy()
# end of clang-tidy things

message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
    ${PROJECT_NAME}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:include>
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/fp/ DESTINATION include/fp)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-O0 -g -std=c++20 -Wall -Wextra -Wpedantic")

add_executable(fp_main main.cpp)
target_include_directories(fp_main PRIVATE include)

subdirs(test)
