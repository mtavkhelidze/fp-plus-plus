#include <exception>
// keep for rapidcheck

#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

#include <fp/fp>

using namespace fp;


constexpr auto square = [](int x) { return x * x; };
constexpr auto hello = [](std::string name) { return "Hello " + name; };
constexpr auto add1 = [](int x) { return x + 1; };
constexpr auto multiply2 = [](int x) { return x * 2; };
constexpr auto greet = [](std::string name) { return "Hello, " + name; };
constexpr auto double_it = [](int x) { return x * 2; };
constexpr auto int_to_string = [](int x) { return std::to_string(x); };
constexpr auto make_multiplier = [](int x) {
    return [x](int y) { return x * y; };
};

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

TEST(Syntax_Operator_Compose, works_with_composition_right_to_left) {
    auto actual = add1 <<= multiply2;
    auto expected = 5;

    EXPECT_EQ(actual(2), expected);
}

TEST(Syntax_Operator_Compose, works_with_multiple_compositions_right_to_left) {
    auto actual = add1 <<= multiply2 <<= add1;
    auto expected = 7;  // add1(2) = 3, multiply2(3) = 6, add1(6) = 7

    EXPECT_EQ(actual(2), expected);
}

TEST(Syntax_Operator_Compose, works_with_identity_function) {
    auto actual = add1 <<= id;
    EXPECT_EQ(actual(2), add1(2));

    auto actual2 = id <<= multiply2;
    EXPECT_EQ(actual2(2), multiply2(2));
}

TEST(Syntax_Operator_Compose, works_with_different_return_types) {
    auto add_exclamation = [](std::string s) { return s + "!"; };

    auto actual = add_exclamation <<= int_to_string <<= add1;
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
    auto add_then_multiply = make_multiplier(3) <<= add1;

    EXPECT_EQ(add_then_multiply(2), 9);  // (2 + 1) * 3 = 9
}

TEST(Syntax_Operator_Pipe, applies_function) { EXPECT_EQ(42 >= add1, 43); }

TEST(Syntax_Operator_Pipe, works_with_lambdas) { EXPECT_EQ(4 >= square, 16); }

TEST(Syntax_Operator_Pipe, supports_chaining) {
    EXPECT_EQ(10 >= double_it >= int_to_string, "20");
}

TEST(Syntax_Operator_Pipe, works_with_void_functions) {
    std::stringstream ss;
    auto print = [&](int x) { ss << x; };

    5 >= print;
    EXPECT_EQ(ss.str(), "5");
}

template <typename A>
struct EqStruct {
    A value;

    inline bool equals(const EqStruct<A>& other) const {
        return value == other.value;
    }
};

RC_GTEST_PROP(Syntax_Eq_Operator_Equals, equality, (const int val)) {
    EqStruct a = {val};
    EqStruct b = {val};
    EqStruct c = {val + 1};

    bool eq = a == b;
    RC_ASSERT(eq);

    auto notEq = a != c;
    RC_ASSERT(notEq);
}

RC_GTEST_PROP(Syntax_Eq_Operator_Equals, reflexivity, (const int val)) {
    EqStruct a = {val};

    bool eq = a == a;
    RC_ASSERT(eq);
}

RC_GTEST_PROP(
  Syntax_Eq_Operator_Equals, symmetry, (const int val1, const int val2)
) {
    EqStruct a = {val1};
    EqStruct b = {val2};

    bool condition = a == b;
    if (condition) {
        bool reverseCondition = b == a;
        RC_ASSERT(reverseCondition);
    }
}

RC_GTEST_PROP(
  Syntax_Eq_Operator_Equals, transitivity,
  (const int val1, const int val2, const int val3)
) {
    EqStruct a = {val1};
    EqStruct b = {val2};
    EqStruct c = {val3};

    bool firstCondition = a == b;
    bool secondCondition = b == c;

    if (firstCondition && secondCondition) {
        bool transitiveCondition = a == c;
        RC_ASSERT(transitiveCondition);
    }
}

struct MonoidStruct {
    using Pair = std::pair<int, int>;
    Pair value;

    inline bool equals(const MonoidStruct& other) const {
        return value == other.value;
    }

    inline MonoidStruct combine(const MonoidStruct& other) const {
        return MonoidStruct{Pair{
          value.first + other.value.first, value.second + other.value.second
        }};
    }

    static MonoidStruct empty() { return MonoidStruct{Pair{0, 0}}; }
};

RC_GTEST_PROP(
  Syntax_Monoid_Operator_Combine, associativity,
  (const std::pair<int, int> v1, const std::pair<int, int> v2,
   const std::pair<int, int> v3)
) {
    MonoidStruct a = {v1};
    MonoidStruct b = {v2};
    MonoidStruct c = {v3};

    auto left = (a + b) + c;
    auto right = a + (b + c);

    bool isEqual = left == right;

    RC_ASSERT(isEqual);
}

RC_GTEST_PROP(
  Syntax_Monoid_Operator_Combine, left_identity, (const std::pair<int, int> v)
) {
    MonoidStruct a = {v};

    auto result = MonoidStruct::empty() + a;
    bool isEqual = result == a;

    RC_ASSERT(isEqual);
}

RC_GTEST_PROP(
  Syntax_Monoid_Operator_Combine, right_identity, (const std::pair<int, int> v)
) {
    MonoidStruct a = {v};

    auto result = a + MonoidStruct::empty();
    bool isEqual = result == a;

    RC_ASSERT(isEqual);
}
