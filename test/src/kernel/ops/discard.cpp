/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <concepts>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Ops_Discard, replaces_value_with_whatever) {
    auto fa = pure<StructWithPure>(42);
    auto result = discard(fa);
    static_assert(std::same_as<decltype(result), StructWithPure<Unit>>);
    ASSERT_EQ(result.value(), whatever);
}

// works over any F<A>
TEST(Kernel_Ops_Discard, works_over_any_inner_type) {
    auto fa = pure<StructWithPure>(42);
    auto fb = pure<StructWithPure>(String("hello"));
    static_assert(std::same_as<decltype(discard(fa)), StructWithPure<Unit>>);
    static_assert(std::same_as<decltype(discard(fb)), StructWithPure<Unit>>);
    ASSERT_EQ(discard(fa).value(), whatever);
    ASSERT_EQ(discard(fb).value(), whatever);
}
