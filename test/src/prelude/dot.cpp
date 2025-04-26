#include <fp/operators/composition.h>
#include <fp/prelude/dot.h>
#include <fp/prelude/identity.h>
#include <gtest/gtest.h>

#include "shorts.h"

using namespace fp::test;
using namespace fp::operators::composition;
using namespace fp::prelude;

// * like . in Haskell
TEST(Prelude_Dot_Operator, works_with_composition_right_to_left) {
    auto initial = 2;
    auto f = increment * triple;
    auto actual = f(initial);
    auto expected = 7;

    EXPECT_EQ(actual, expected);
}

TEST(Prelude_Dot_Operator, works_with_multiple_compositions_right_to_left) {
    auto inittial = 2;
    auto f = increment * triple * increment;
    auto actual = 10;
    auto expected = f(inittial);

    EXPECT_EQ(actual, expected);
}

TEST(Prelude_Dot_Operator, works_with_identity_function) {
    auto actual = increment * identity;
    EXPECT_EQ(actual(2), increment(2));

    auto actual2 = identity * triple;
    EXPECT_EQ(actual2(2), triple(2));
}

TEST(Prelude_Dot_Operator, works_with_different_return_types) {
    auto add_exclamation = [](std::string s) { return s + "!"; };

    auto actual = add_exclamation * int_to_string * increment;
    EXPECT_EQ(actual(42), "43!");
}

TEST(Prelude_Dot_Operator, works_with_nested_lambdas) {
    auto add_then_multiply = make_multiplier(3) * increment;

    EXPECT_EQ(add_then_multiply(2), 9);  // (2 + 1) * 3 = 9
}

TEST(Prelude_Dot_Operator, forwards_arguments_correctly) {
    auto to_string = [](const int& x) -> std::string {
        return std::to_string(x);
    };
    auto add_suffix = [](std::string&& s) -> std::string {
        return s + "_done";
    };

    auto f = add_suffix * to_string;
    EXPECT_EQ(f(123), "123_done");
}

TEST(
  Prelude_Dot_Operator, composed_function_is_noexcept_if_parts_are_noexcept
) {
    auto no_throw1 = [](int x) noexcept { return x + 1; };
    auto no_throw2 = [](int x) noexcept { return x * 2; };

    auto f = no_throw1 * no_throw2;
    static_assert(noexcept(f(42)), "Composition should be noexcept");
}

TEST(Prelude_Dot_Operator, works_with_structs_and_pairs) {
    auto make_pair = [](int x) { return std::make_pair(x, std::to_string(x)); };
    auto format_pair = [](const std::pair<int, std::string>& p) {
        return p.second + "_" + std::to_string(p.first);
    };

    auto f = format_pair * make_pair;
    EXPECT_EQ(f(7), "7_7");
}

struct Adder {
    int operator()(int x) const { return x + 1; }
};

struct Multiplier {
    int operator()(int x) const { return x * 2; }
};

TEST(Prelude_Dot_Operator, works_with_custom_functions_objects) {
    auto f = Adder{} * Multiplier{};
    EXPECT_EQ(f(2), 5);
}
