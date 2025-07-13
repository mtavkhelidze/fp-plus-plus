#include <fp/core/nothing.h>
#include <fp/internal/mixins/value.h>
#include <fp/prelude/pure.h>
#include <fp/tools/value.h>
#include <fp/traits/all.h>
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

// TEST(Mixin_WithValue, backend_choice) {
//     constexpr int arr[] = {1, 2, 3};
//     const TestStruct da1 = pure<TestStruct>(arr);
//     EXPECT_TRUE(da1.is_box());
//     EXPECT_FALSE(da1.is_stack());
//     EXPECT_EQ(da1.value().at(2), 3);

//     TestStruct const da2 = pure<TestStruct>(42);
//     EXPECT_FALSE(da2.is_box());
//     EXPECT_TRUE(da2.is_stack());
//     EXPECT_EQ(da2.value(), 42);
// }

TEST(Mixin_WithValue, empty) {
    TestStruct<Nothing> da;
    EXPECT_TRUE(da.is_box());
    EXPECT_EQ(da.value(), nothing);
}

TEST(Mixin_WithValue, static_apply_direct) {
    auto val = TestStruct<int>::apply(123);
    static_assert(std::is_same_v<decltype(val), TestStruct<int>>);
    EXPECT_EQ(val.value(), 123);
}

TEST(Mixin_WithValue, traits) {
    static_assert(HasApply<TestStruct<int>>);
    static_assert(HasValue<TestStruct<int>>);
}
