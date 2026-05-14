#include <fp/fp.h>
#include <gtest/gtest.h>

#include <concepts>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct
    : WithApply<TestStruct<A>>
    , WithFunctor<TestStruct<A>> {};

// discard replaces value with nothing, preserves structure
TEST(Kernel_Ops_Discard, replaces_value_with_nothing) {
    auto fa = pure<TestStruct>(42);
    auto result = discard(fa);
    static_assert(std::same_as<decltype(result), TestStruct<Nothing>>);
    ASSERT_EQ(result.value(), nothing);
}

// works over any F<A>
TEST(Kernel_Ops_Discard, works_over_any_inner_type) {
    auto fa = pure<TestStruct>(42);
    auto fb = pure<TestStruct>(String("hello"));
    static_assert(std::same_as<decltype(discard(fa)), TestStruct<Nothing>>);
    static_assert(std::same_as<decltype(discard(fb)), TestStruct<Nothing>>);
    ASSERT_EQ(discard(fa).value(), nothing);
    ASSERT_EQ(discard(fb).value(), nothing);
}
