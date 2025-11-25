vcpkg_install(gtest)
vcpkg_install(rapidcheck)

find_package(GTest CONFIG REQUIRED)
find_package(rapidcheck CONFIG REQUIRED)
target_compile_options(rapidcheck INTERFACE -Wno-deprecated-declarations)

set(TEST_LIB fp++ GTest::gtest GTest::gtest_main GTest::gmock rapidcheck_gtest)
set(TEST_SRC
    # src/internal/storage/box_storage.cpp
    # src/internal/storage/box.cpp
    # src/internal/storage/stack_storage.cpp
    # src/prelude/compose.cpp
    # src/prelude/dollar.cpp
    # src/prelude/flip.cpp
    # src/prelude/identity.cpp
    # src/prelude/pipe.cpp
    # src/tools/cast.cpp
    # src/type/eq/eq_ops.cpp
    # src/type/eq/eq_props.cpp
    # src/type/eq/eq_traits.cpp
    src/type/functor/functor_props.cpp
    # src/type/value/value_lift.cpp
    # src/type/value/value_pure.cpp
    # src/type/value/value_traits.cpp
)

set(TEST_HEADERS
    src/type/eq/eq_types.h
    src/type/functor/functor_types.h
    src/type/value/value_types.h
)
# find_untracked_files("${TEST_SRC}" src "*.cpp")
# find_untracked_files("${TEST_HEADERS}" src "*.h")

add_executable(${PROJECT_NAME}_test ${TEST_SRC} ${TEST_HEDERS})
target_compile_definitions(${PROJECT_NAME}_test PRIVATE FP_PLUS_PLUS_TESTING)
target_compile_definitions(
    ${PROJECT_NAME}_test PRIVATE FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
)
target_compile_definitions(
    ${PROJECT_NAME}_test PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS
)
# Uncomment below if you want to check for memory leaks

# target_compile_options(${PROJECT_NAME}_test PRIVATE -fsanitize=address)
# target_link_options(${PROJECT_NAME}_test PRIVATE -fsanitize=address)

target_include_directories(${PROJECT_NAME}_test PRIVATE include)
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${TEST_LIB})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)
