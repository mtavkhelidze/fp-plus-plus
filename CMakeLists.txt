cmake_minimum_required(VERSION 3.30)
project(
    FP++
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/third_party/vcpkg")
    execute_process(
        COMMAND git submodule update --init --recursive
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE result
    )
    if(result)
        message(FATAL_ERROR "Git submodule update failed!")
    endif()
endif()

set(CMAKE_TOOLCHAIN_FILE
    ${CMAKE_SOURCE_DIR}/third_party/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file"
)
set(VCPKG_ROOT ${CMAKE_SOURCE_DIR}/third_party/vcpkg)

find_package(GTest REQUIRED)

include_directories(include)

add_executable(fp_test test/syntax.cpp)
target_link_libraries(fp_test PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME F++Test COMMAND fp_test)
