#include <exception>
// keep for rapidcheck

#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

#include <fp/fp>

using namespace fp;

auto multiplyByTwo = [](auto x) { return x * 2; };
auto addOne = [](auto x) { return x + 1; };

RC_GTEST_PROP(Option_Map, identity_law, (const int val)) {
    auto actual = Some(val).map(id);
    RC_ASSERT(actual == Some(val));
}

RC_GTEST_PROP(Option_Map, composition_law, (const int val)) {
    auto actual = Some(val).map(multiplyByTwo).map(addOne);
    auto expected = Some(val).map(addOne <<= multiplyByTwo);
    RC_ASSERT(actual == expected);
}

RC_GTEST_PROP(Option_Map, homomorphism_law, (const int val)) {
    auto actual = Some(val).map(addOne);
    auto expected = Some(addOne &= val);
    RC_ASSERT(actual == expected);
}

RC_GTEST_PROP(Option_Map, identity_law_none, ()) {
    auto actual = None<int>().map(id);
    RC_ASSERT(actual == None<int>());
}

RC_GTEST_PROP(Option_Map, composition_law_none, ()) {
    auto actual = None<int>().map(multiplyByTwo).map(addOne);
    auto expected = None<int>().map(addOne <<= multiplyByTwo);
    RC_ASSERT(actual == expected);
}

RC_GTEST_PROP(Option_Map, homomorphism_law_none, ()) {
    auto actual = None<int>().map(addOne);
    auto expected = None<int>();
    RC_ASSERT(actual == expected);
}

RC_GTEST_PROP(Option_Equals, reflexivity_some, (const int val)) {
    auto someVal = Some(val);
    RC_ASSERT(someVal.equals(someVal));
}

RC_GTEST_PROP(Option_Equals, reflexivity_none, ()) {
    auto noneVal = None<int>();
    RC_ASSERT(noneVal.equals(noneVal));
}

RC_GTEST_PROP(Option_Equals, symmetry, (const int val1, const int val2)) {
    auto some1 = Some(val1);
    auto some2 = Some(val2);
    RC_ASSERT((some1.equals(some2)) == (some2.equals(some1)));
}

RC_GTEST_PROP(Option_Equals, transitivity, (const int val)) {
    auto some1 = Some(val);
    auto some2 = Some(val);
    auto some3 = Some(val);
    RC_ASSERT(
      some1.equals(some2) && some2.equals(some3) && some1.equals(some3)
    );
}

RC_GTEST_PROP(Option_Equals, none_not_equal_some, (const int val)) {
    auto someVal = Some(val);
    auto noneVal = None<int>();
    RC_ASSERT(!someVal.equals(noneVal));
    RC_ASSERT(!noneVal.equals(someVal));
}

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
