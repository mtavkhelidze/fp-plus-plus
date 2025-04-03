
#include <gtest/gtest.h>

#include <fp/fp.h>

#include "shorts.h"

using namespace fp;

auto some = Some(42);
auto none = None<int>();

TEST(Option_Some, should_work) {
    EXPECT_TRUE(some.isSome());
    EXPECT_FALSE(none.isSome());
}

TEST(Option_None, should_work) {
    EXPECT_FALSE(some.isNone());
    EXPECT_TRUE(none.isNone());
}
