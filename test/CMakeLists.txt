
add_executable(${PROJECT_NAME}_test syntax.cpp)
target_link_libraries(
    ${PROJECT_NAME}_test PRIVATE gtest::gtest gtest::gtest_main
)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)
