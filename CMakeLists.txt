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

add_library(
    ${PROJECT_NAME}
    INTERFACE
    include/fp/data/data.h
    include/fp/data/monad/id.h
    include/fp/data/nothing.h
    include/fp/debug.h
    include/fp/fp.h
    include/fp/internal/box.h
    include/fp/internal/storage/storage_box.h
    include/fp/internal/storage/storage_provider.h
    include/fp/internal/storage/storage_stack.h
    include/fp/operators.h
    include/fp/prelude/defs.h
    include/fp/prelude/dollar.h
    include/fp/prelude/dot.h
    include/fp/prelude/flip.h
    include/fp/prelude/identity.h
    include/fp/prelude/pipe.h
    include/fp/prelude/prelude.h
    include/fp/prelude/pure.h
    include/fp/tools.h
    include/fp/tools/tc.h
    include/fp/traits/applicative.h
    include/fp/traits/eq.h
    include/fp/traits/functor.h
    include/fp/traits/monad.h
    include/fp/traits/monoid.h
    include/fp/traits/object.h
    include/fp/traits/semigroup.h
    include/fp/traits/traits.h
)
target_include_directories(
    ${PROJECT_NAME}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:include>
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/fp/ DESTINATION include/fp)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-O1 -g -Wall -Wextra -Wpedantic")

add_executable(fp_main main.cpp)
target_compile_definitions(fp_main PRIVATE FP_PLUS_PLUS_TESTING)
target_include_directories(fp_main PRIVATE include)

subdirs(test)
