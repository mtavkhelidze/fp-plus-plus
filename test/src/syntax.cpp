// NOLINTBEGIN:-hicpp-named-parameter,-readability-named-parameter,llvmlibc-implementation-in-namespace

#include <fp/fp.h>
#include <gtest/gtest.h>

#include "shorts.h"

using namespace fp;
using namespace fp::test;
using namespace fp::syntax;
using namespace fp::functions;

// &= like $ in Haskell
TEST(Syntax_Operator_Dollar, works_with_different_types) {
    auto actual = int_to_string &= square &= 2;
    auto expected = "4";

    EXPECT_EQ(actual, expected);
}

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

// <<= like . in Haskell
TEST(Syntax_Operator_Compose, works_with_composition_right_to_left) {
    auto initial = 2;
    auto f = increment <<= triple;
    auto actual = f(initial);
    auto expected = 7;

    EXPECT_EQ(actual, expected);
}

TEST(Syntax_Operator_Compose, works_with_multiple_compositions_right_to_left) {
    auto inittial = 2;
    auto f = increment <<= triple <<= increment;
    auto actual = 10;
    auto expected = f(inittial);

    EXPECT_EQ(actual, expected);
}

TEST(Syntax_Operator_Compose, works_with_identity_function) {
    auto actual = increment <<= id;
    EXPECT_EQ(actual(2), increment(2));

    auto actual2 = id <<= triple;
    EXPECT_EQ(actual2(2), triple(2));
}

TEST(Syntax_Operator_Compose, works_with_different_return_types) {
    auto add_exclamation = [](std::string s) { return s + "!"; };

    auto actual = add_exclamation <<= int_to_string <<= increment;
    EXPECT_EQ(actual(42), "43!");
}

TEST(Syntax_Operator_Compose, works_with_void_return) {
    std::stringstream ss;
    auto print = [&](int x) { ss << x; };
    auto double_it = [](int x) { return x * 2; };

    auto composed = print <<= double_it;
    composed(5);

    EXPECT_EQ(ss.str(), "10");
}

TEST(Syntax_Operator_Compose, works_with_nested_lambdas) {
    auto add_then_multiply = make_multiplier(3) <<= increment;

    EXPECT_EQ(add_then_multiply(2), 9);  // (2 + 1) * 3 = 9
}

// >= like |> in Elm
TEST(Syntax_Operator_Pipe, applies_function) { EXPECT_EQ(42 >= increment, 43); }

TEST(Syntax_Operator_Pipe, works_with_lambdas) { EXPECT_EQ(4 >= square, 16); }

TEST(Syntax_Operator_Pipe, supports_chaining) {
    EXPECT_EQ(10 >= triple >= int_to_string, "30");
}

TEST(Syntax_Operator_Pipe, works_with_void_functions) {
    std::stringstream ss;
    auto print = [&](int x) { ss << x; };

    5 >= print;
    EXPECT_EQ(ss.str(), "5");
}
// NOLINTEND
