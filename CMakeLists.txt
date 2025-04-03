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

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

include_directories(include)
subdirs(test)
