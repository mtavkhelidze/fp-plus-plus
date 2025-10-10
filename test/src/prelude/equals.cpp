#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::mixins;
using namespace fp::operators;

template <typename A>
struct TestStruct
    : WithValue<TestStruct<A>>
    , WithEq<TestStruct, A> {
  private:
    using Base = WithValue<TestStruct>;
    using Base::Base;
};

TEST(Prelude_Euqals, equal_values) {
    auto a = pure<TestStruct>(10);
    auto b = pure<TestStruct>(10);
    ASSERT_TRUE(equals(a, b));
    ASSERT_FALSE(!equals(a, b));
}

TEST(Prelude_Euqals, non_equal_values) {
    auto a = pure<TestStruct>(10);
    auto b = pure<TestStruct>(13);
    ASSERT_FALSE(equals(a, b));
    ASSERT_TRUE(!equals(a, b));
}

TEST(Operators_Euqality, double_equal) {
    auto a = pure<TestStruct>(10);
    auto b = pure<TestStruct>(10);
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
}

TEST(Prelude_Euqals, negative_double_equal) {
    auto a = pure<TestStruct>(10);
    auto b = pure<TestStruct>(13);
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}
