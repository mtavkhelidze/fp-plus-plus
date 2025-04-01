#include <gtest/gtest.h>

#include <fp/fp>

using namespace fp;
#include <gtest/gtest.h>

#include <fp/fp>

using namespace fp;

TEST(Option_isSome, should_return_true) {
    auto someVal = Some(42);
    EXPECT_TRUE(someVal.isSome());
    EXPECT_FALSE(someVal.isNone());
}

TEST(Option_isNone, should_return_true) {
    auto noneVal = None<int>();
    EXPECT_TRUE(noneVal.isNone());
    EXPECT_FALSE(noneVal.isSome());
}

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

TEST(Option_isSome, should_return_true_for_some) {
    auto someVal = Some(42);
    EXPECT_TRUE(someVal.isSome());
}

TEST(Option_isNone, should_return_true_for_none) {
    auto noneVal = None<int>();
    EXPECT_TRUE(noneVal.isNone());
}
