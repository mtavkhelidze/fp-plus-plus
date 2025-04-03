
#include <gtest/gtest.h>

#include <fp/fp>

#include "shorts.h"

using namespace fp;

TEST(Option_get, should_throw_exception_for_none) {
    auto noneVal = None<int>();
    EXPECT_THROW(noneVal.get(), std::runtime_error);
}

TEST(Option_get, should_return_value_for_some) {
    auto someVal = Some(42);
    EXPECT_EQ(someVal.get(), 42);
}

TEST(Option_getOrElse, should_return_fallback_for_none) {
    auto noneVal = None<int>();
    EXPECT_EQ(noneVal.getOrElse(0), 0);
}

TEST(Option_getOrElse, should_return_value_for_some) {
    auto someVal = Some(42);
    EXPECT_EQ(someVal.getOrElse(0), 42);
}
