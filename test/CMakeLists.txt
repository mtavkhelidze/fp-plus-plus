find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}_test syntax.cpp)
target_link_libraries(
    ${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main
)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)
