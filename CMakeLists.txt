cmake_minimum_required(VERSION 3.30)

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

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/vcpkg")
    execute_process(
        COMMAND git submodule update --init --recursive
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE res
    )
    if(res)
        message(FATAL_ERROR "Git submodule update failed!")
    endif()

    execute_process(
        COMMAND ./bootstrap-vcpkg.sh -dissableMetrics
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
        RESULT_VARIABLE res
    )
    if(res)
        message(FATAL_ERROR "vcpkg bootstrap failed!")
    endif()

    message(STATUS "vcpkg Root: ${VCPKG_ROOT}")
    set(VCPKG_ROOT ${CMAKE_SOURCE_DIR}/vcpkg)
    message(STATUS "vcpkg Toochain: ${CMAKE_TOOLCHAIN_FILE}")
    set(CMAKE_TOOLCHAIN_FILE
        ${CMAKE_SOURCE_DIR}/third_party/vcpkg/scripts/buildsystems/vcpkg.cmake
    )
endif()

include_directories(include)
# subdirs(test)
