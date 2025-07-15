#include <fp/core/all.h>
#include <fp/internal/mixins/value.h>
#include <fp/prelude/pure.h>
#include <fp/traits/all.h>
#include <fp/traits/value.h>
#include <gtest/gtest.h>

using namespace fp::core;
using namespace fp::traits;
using namespace fp::prelude;
using namespace fp::prelude;
using namespace fp::internal::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

TEST(Mixin_WithValue, empty) {
    TestStruct<Nothing> da = TestStruct<Nothing>::apply(nothing);
    EXPECT_TRUE(da.is_box());
    EXPECT_EQ(da.value(), nothing);
}

TEST(Mixin_WithValue, static_apply_direct) {
    TestStruct<int> val = TestStruct<int>::apply(123);
    static_assert(std::is_same_v<decltype(val), TestStruct<int>>);
    EXPECT_EQ(val.value(), 123);
}

TEST(Mixin_WithValue, satisfy_value_and_apply_traits) {
    static_assert(HasApply<TestStruct<int>>);
    static_assert(HasValue<TestStruct<int>>);
}
