find_package(GTest CONFIG REQUIRED)
find_package(rapidcheck CONFIG REQUIRED)
target_compile_options(rapidcheck INTERFACE -Wno-deprecated-declarations)

set(TEST_LIB GTest::gtest GTest::gtest_main GTest::gmock rapidcheck_gtest)
set(TEST_SRC syntax.cpp option.cpp)

add_executable(${PROJECT_NAME}_test ${TEST_SRC})
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${TEST_LIB})
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)
