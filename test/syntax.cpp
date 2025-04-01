#include <gtest/gtest.h>

#include <fp/fp>

using namespace fp;

constexpr auto square = [](int x) { return x * x; };
constexpr auto hello = [](std::string name) { return "Hello " + name; };

TEST(Syntax_Operator_Dollar, works_with_primitive_type) {
    auto actual = square &= 2;
    auto expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST(Syntax_Operator_Dollar, works_with_string_type) {
    auto actual = hello &= "Name";
    auto expected = "Hello Name";

    EXPECT_EQ(actual, expected);
}

TEST(Syntax_Operator_Dollar, works_function_returning_value) {
    auto actual = square &= square(2);
    auto expected = 16;

    EXPECT_EQ(actual, expected);
}

TEST(Syntax_Operator_Dollar, works_multiple_function_application) {
    auto actual = square &= square &= square(2);
    auto expected = 16 * 16;

    EXPECT_EQ(actual, expected);
}
