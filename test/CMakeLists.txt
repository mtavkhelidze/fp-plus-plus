find_package(GTest CONFIG REQUIRED)
find_package(rapidcheck CONFIG REQUIRED)

target_compile_options(rapidcheck INTERFACE -Wno-deprecated-declarations)

add_executable(${PROJECT_NAME}_test syntax.cpp option.cpp)
target_link_libraries(
    ${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main
                                 rapidcheck_gtest
)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)
