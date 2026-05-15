#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <concepts>

using namespace fp;
using namespace fp::test;

// discard replaces value with nothing, preserves structure
TEST(Kernel_Ops_Discard, replaces_value_with_nothing) {
    auto fa = pure<StructWithPure>(42);
    auto result = discard(fa);
    static_assert(std::same_as<decltype(result), StructWithPure<Nothing>>);
    ASSERT_EQ(result.value(), nothing);
}

// works over any F<A>
TEST(Kernel_Ops_Discard, works_over_any_inner_type) {
    auto fa = pure<StructWithPure>(42);
    auto fb = pure<StructWithPure>(String("hello"));
    static_assert(std::same_as<decltype(discard(fa)), StructWithPure<Nothing>>);
    static_assert(std::same_as<decltype(discard(fb)), StructWithPure<Nothing>>);
    ASSERT_EQ(discard(fa).value(), nothing);
    ASSERT_EQ(discard(fb).value(), nothing);
}
