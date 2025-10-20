#include <fp/fp.h>
#include <gtest/gtest.h>

#include "eq_types.h"

using namespace fp;
using namespace fp::operators;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

TEST(Eq_Props, reflexivity) {
    auto a = pure<EqStruct>(42);
    EXPECT_TRUE(a.equals(a));
}

TEST(Eq_Props, symmetry) {
    auto a = pure<EqStruct>(42);
    auto b = pure<EqStruct>(42);
    EXPECT_EQ(a.equals(b), b.equals(a));
}

TEST(Eq_Props, transitivity) {
    auto a = pure<EqStruct>(42);
    auto b = pure<EqStruct>(42);
    auto c = pure<EqStruct>(42);
    if (a.equals(b) && b.equals(c)) {
        EXPECT_TRUE(a.equals(c));
    }
}

TEST(Eq_Prelude_Equals, equal_values) {
    auto a = pure<EqStruct>(10);
    auto b = pure<EqStruct>(10);
    ASSERT_TRUE(equals(a, b));
    ASSERT_FALSE(!equals(a, b));
}

TEST(Eq_Prelude_Equals, non_equal_values) {
    auto a = pure<EqStruct>(10);
    auto b = pure<EqStruct>(13);
    ASSERT_FALSE(equals(a, b));
    ASSERT_TRUE(!equals(a, b));
}

TEST(Eq_Operators_Equals, double_equal) {
    auto a = pure<EqStruct>(10);
    auto b = pure<EqStruct>(10);
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
}

TEST(Eq_Operators_Equals, negative_double_equal) {
    auto a = pure<EqStruct>(10);
    auto b = pure<EqStruct>(13);
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}

TEST(Eq_Prelude_Equals, ordinary_type_equals) {
    std::string a("hello");
    std::string b("hello");
    ASSERT_TRUE(equals(a, b));
    ASSERT_FALSE(!equals(a, b));
}

TEST(Eq_Prelude_Equals, ordinary_type_not_equals) {
    std::string a("hello");
    std::string b("bye");
    ASSERT_FALSE(equals(a, b));
    ASSERT_TRUE(!equals(a, b));
}

TEST(Eq_Operators_Equals, ordinary_type_equals) {
    std::string a("hello");
    std::string b("hello");
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
}

TEST(Eq_Operators_Equals, ordinary_type_not_equals) {
    std::string a("hello");
    std::string b("bye");
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}

TEST(Prelude_Equals, custom_operators_equal_values) {
    auto a = CustomWithOperators{10};
    auto b = CustomWithOperators{10};
    ASSERT_TRUE(equals(a, b));
    ASSERT_FALSE(!equals(a, b));
}

TEST(Prelude_Equals, custom_operators_equal_not) {
    auto a = CustomWithOperators{10};
    auto b = CustomWithOperators{13};
    ASSERT_FALSE(equals(a, b));
    ASSERT_TRUE(!equals(a, b));
}

TEST(Operators_Equals, custom_operators_equal) {
    auto a = CustomWithOperators{10};
    auto b = CustomWithOperators{10};
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
}

TEST(Operators_Equals, custom_operators_equal_not) {
    auto a = CustomWithOperators{10};
    auto b = CustomWithOperators{13};
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}

TEST(Prelude_Equals, custom_with_eq_equal) {
    auto a = CustomWithEq<int>{10};
    auto b = CustomWithEq<int>{10};
    ASSERT_TRUE(equals(a, b));
    ASSERT_FALSE(!equals(a, b));
}

TEST(Prelude_Equals, custom_with_eq_equal_not) {
    auto a = CustomWithEq<int>{10};
    auto b = CustomWithEq<int>{13};
    ASSERT_FALSE(equals(a, b));
    ASSERT_TRUE(!equals(a, b));
}

TEST(Operators_Equals, custom_with_eq_equal) {
    auto a = CustomWithEq<int>{10};
    auto b = CustomWithEq<int>{10};
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
}

TEST(Operators_Equals, custom_with_eq_equal_not) {
    auto a = CustomWithEq<int>{10};
    auto b = CustomWithEq<int>{13};
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}

// NOLINTEND(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
