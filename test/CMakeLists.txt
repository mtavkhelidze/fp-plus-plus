vcpkg_install(rapidcheck)
vcpkg_install(gtest)

find_package(GTest CONFIG REQUIRED)
find_package(rapidcheck CONFIG REQUIRED)
target_compile_options(
    rapidcheck
    INTERFACE -Wno-deprecated-declarations
)

set(TEST_SRC
    src/core/applicative.cpp
    src/core/functor.cpp
    src/data/nothing.cpp
    src/internal/meta/cast.cpp
    src/internal/meta/rebind.cpp
    src/internal/storage/box_storage.cpp
    src/internal/storage/box.cpp
    src/internal/storage/stack_storage.cpp
    src/kernel/mixins/with_applicative.cpp
    src/kernel/mixins/with_functor.cpp
    src/kernel/mixins/with_pure.cpp
    src/kernel/ops/always.cpp
    src/kernel/ops/ap.cpp
    src/kernel/ops/as.cpp
    src/kernel/ops/compose.cpp
    src/kernel/ops/discard.cpp
    src/kernel/ops/fmap.cpp
    src/kernel/ops/fproduct.cpp
    src/kernel/ops/lift.cpp
    src/kernel/ops/pipe.cpp
    src/kernel/ops/pure.cpp
    src/syntax/operators.cpp
)
set(TEST_HEADERS
)
# find_untracked_files("${TEST_SRC}" src "*.cpp")
# find_untracked_files("${TEST_HEADERS}" src "*.h")
add_executable(
    ${PROJECT_NAME}_test
    ${TEST_SRC} ${TEST_HEADERS}
)
target_compile_definitions(
    ${PROJECT_NAME}_test
    PRIVATE FP_PLUS_PLUS_TESTING)
target_compile_definitions(
    ${PROJECT_NAME}_test
    PRIVATE FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
)
target_compile_options(
    ${PROJECT_NAME}_test
    PRIVATE
    -g
    -Wall
    -Werror
    -Wextra
    -Wpedantic
)
target_include_directories(
    ${PROJECT_NAME}_test
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
    ${PROJECT_NAME}_test
    ${PROJECT_NAME}
    GTest::gtest_main
    rapidcheck_gtest
)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)

# target_compile_definitions(
#     ${PROJECT_NAME}_test PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS
# )

# Uncomment below if you want to check for memory leaks
# target_compile_options(${PROJECT_NAME}_test PRIVATE -fsanitize=address)
# target_link_options(${PROJECT_NAME}_test PRIVATE -fsanitize=address)
