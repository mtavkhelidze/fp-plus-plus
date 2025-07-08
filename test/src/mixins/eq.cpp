
#include <fp/mixins/eq.h>
#include <fp/operators/eq.h>
#include <fp/prelude/pure.h>
#include <fp/traits/eq.h>
#include <gtest/gtest.h>

using namespace fp::prelude;
using namespace fp::operators::eq;
using namespace fp::traits::eq;

template <typename A>
struct TestStruct : fp::mixins::eq::WithEq<TestStruct<A>> {
  private:
    using Base = fp::mixins::eq::WithEq<TestStruct<A>>;
    using Base::Base;
};

TEST(Mixin_WithEq, traits) { static_assert(Eq<TestStruct<int>>); }

TEST(Mixin_WithEq, is_Eq) {  //
    auto a = pure<TestStruct>(10);
    auto b = pure<TestStruct>(10);
    ASSERT_TRUE(a.equals(b));
}

TEST(Mixin_WithValue, is_Eq_complex) {
    static_assert(fp::traits::eq::Eq<TestStruct<std::vector<int>>>);
    TestStruct const da1 = pure<TestStruct>(std::vector{1, 2, 3});
    TestStruct const da2 = pure<TestStruct>(std::vector{1, 2, 3});
    TestStruct const da3 = pure<TestStruct>(std::vector{3, 2, 1});
    EXPECT_TRUE(da1 == da2);
    EXPECT_TRUE(da1 != da3);
}

TEST(Mixin_WithValue, is_Eq_fundamental) {
    static_assert(fp::traits::eq::Eq<TestStruct<int>>);
    TestStruct const da1 = pure<TestStruct>(42);
    TestStruct const da2 = pure<TestStruct>(42);
    TestStruct const da3 = pure<TestStruct>(24);
    EXPECT_TRUE(da1 == da2);
    EXPECT_TRUE(da1 != da3);
}
