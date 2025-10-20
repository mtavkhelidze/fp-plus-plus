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

// NOLINTEND(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
