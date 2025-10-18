// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/fp.h>
#include <gtest/gtest.h>

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

#include "eq_test.h"

using namespace fp;
using namespace fp::traits;

TEST(Traits_Eq, has_and_is_traits) {
    static_assert(IsEq<TestStruct>);
    static_assert(HasEquals<TestStruct>);
}

TEST(Types_Eq, reflexivity) {
    auto a = pure<TestStruct>(42);
    EXPECT_TRUE(a.equals(a));
}

TEST(Types_Eq, symmetry) {
    auto a = pure<TestStruct>(42);
    auto b = pure<TestStruct>(42);
    EXPECT_EQ(a.equals(b), b.equals(a));
}

TEST(Types_Eq, transitivity) {
    auto a = pure<TestStruct>(42);
    auto b = pure<TestStruct>(42);
    auto c = pure<TestStruct>(42);
    if (a.equals(b) && b.equals(c)) {
        EXPECT_TRUE(a.equals(c));
    }
}

// NOLINTEND(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
