#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct
    : WithApply<TestStruct<A>>
    , WithFunctor<TestStruct<A>> {};

static_assert(IsFunctor<TestStruct>, "TestStruct must be a functor");
static_assert(HasMap<TestStruct<int>>, "TestStruct must have map method");

TEST(Kernal_Mixins_WithFunctor, map_is_callable) {
    auto val = pure<TestStruct>(42);
    EXPECT_EQ(42, val.map(id).value());
}

TEST(Kernel_Mixins_WithFunctor, as_is_callable) {
    auto val = pure<TestStruct>(42);
    ASSERT_EQ(val.as(String("hello")).value(), "hello");
}

TEST(Kernel_Mixins_WithFunctor, discard_is_callable) {
    auto val = pure<TestStruct>(42);
    ASSERT_EQ(val.discard().value(), nothing);
}
