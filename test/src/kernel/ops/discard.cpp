#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <concepts>

using namespace fp;
using namespace fp::test;

// discard replaces value with nothing, preserves structure
TEST(Kernel_Ops_Discard, replaces_value_with_nothing) {
    auto fa = pure<StructApply>(42);
    auto result = discard(fa);
    static_assert(std::same_as<decltype(result), StructApply<Nothing>>);
    ASSERT_EQ(result.value(), nothing);
}

// works over any F<A>
TEST(Kernel_Ops_Discard, works_over_any_inner_type) {
    auto fa = pure<StructApply>(42);
    auto fb = pure<StructApply>(String("hello"));
    static_assert(std::same_as<decltype(discard(fa)), StructApply<Nothing>>);
    static_assert(std::same_as<decltype(discard(fb)), StructApply<Nothing>>);
    ASSERT_EQ(discard(fa).value(), nothing);
    ASSERT_EQ(discard(fb).value(), nothing);
}
