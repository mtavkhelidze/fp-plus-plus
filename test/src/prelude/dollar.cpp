#include <fp/operators/composition.h>
#include <gtest/gtest.h>

#include "shorts.h"

using namespace fp::test;
using namespace fp::operators::composition;

// &= like $ in Haskell
TEST(Prelude_Dollar_Operator, works_with_different_types) {
    auto actual = int_to_string &= square &= 2;
    auto expected = "4";

    EXPECT_EQ(actual, expected);
}

TEST(Prelude_Dollar_Operator, works_with_primitive_type) {
    auto actual = square &= 2;
    auto expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST(Prelude_Dollar_Operator, works_with_string_type) {
    auto actual = hello &= "Name";
    auto expected = "Hello Name";

    EXPECT_EQ(actual, expected);
}

TEST(Prelude_Dollar_Operator, works_function_returning_value) {
    auto actual = square &= square(2);
    auto expected = 16;

    EXPECT_EQ(actual, expected);
}

TEST(Prelude_Dollar_Operator, works_multiple_function_application) {
    auto actual = square &= square &= square(2);
    auto expected = 16 * 16;

    EXPECT_EQ(actual, expected);
}

constexpr auto inc = [](int x) -> int { return x + 1; };
TEST(Prelude_Dollar_Operator, constexpr_evaluation) {
    constexpr auto result = inc &= inc &= inc &= 1;
    static_assert(
      result == 4, "Constexpr dollar operator should work correctly"
    );
    EXPECT_EQ(result, 4);
}

TEST(Prelude_Dollar_Operator, deep_chaining) {
    auto inc = [](int x) { return x + 1; };

    auto result = inc &= inc &= inc &= inc &= inc &= inc &= inc &=
      0;  // 7 increments

    EXPECT_EQ(result, 7);
}
