vcpkg_install(gtest)
vcpkg_install(rapidcheck)

find_package(GTest CONFIG REQUIRED)
find_package(rapidcheck CONFIG REQUIRED)
target_compile_options(rapidcheck INTERFACE -Wno-deprecated-declarations)

set(TEST_LIB fp++ GTest::gtest GTest::gtest_main GTest::gmock rapidcheck_gtest)
set(TEST_SRC
    # src/core/data/id.cpp
    # src/core/types/functor.cpp
    # src/mixins/eq.cpp
    # src/mixins/flat_map.cpp
    # src/mixins/map.cpp
    # src/prelude/fmap.cpp
    src/internal/mixins/value.cpp
    src/internal/storage/box.cpp
    src/internal/storage/storage_box.cpp
    src/internal/storage/storage_stack.cpp
    src/internal/tools/cast.cpp
    src/prelude/compose.cpp
    src/prelude/dollar.cpp
    src/prelude/flip.cpp
    src/prelude/lift.cpp
    src/prelude/pipe.cpp
    src/prelude/pure.cpp
)

# find_untracked_files("${TEST_SRC}" src "*.cpp")

add_executable(${PROJECT_NAME}_test ${TEST_SRC})
target_compile_definitions(${PROJECT_NAME}_test PRIVATE FP_PLUS_PLUS_TESTING)
target_compile_definitions(
    ${PROJECT_NAME}_test PRIVATE FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
)
target_compile_definitions(
    ${PROJECT_NAME}_test PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS
)
# target_compile_options(${PROJECT_NAME}_test PRIVATE -fsanitize=address)
# target_link_options(${PROJECT_NAME}_test PRIVATE -fsanitize=address)

target_include_directories(${PROJECT_NAME}_test PRIVATE include)
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${TEST_LIB})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)
