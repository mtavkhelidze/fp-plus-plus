/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <string>

using namespace fp;
using namespace fp::test;

// same type
TEST(Kernel_Ops_Product, same_primitive_type) {
    auto fa = pure<StructApplicative>(9);
    auto fb = pure<StructApplicative>(5);
    auto pfa = product(fa);

    auto actual = pfa(fb).value();
    auto expected = pure<StructApplicative>(Tuple{9, 5}).value();
    ASSERT_EQ(actual, expected);
}

// different types
// zip is an alias
TEST(Kernel_Ops_Product, mixed_primitive_and_complex_types) {
    auto fa = pure<StructApplicative>("nine");
    auto fb = pure<StructApplicative>(5);
    auto pfa = zip(fa);

    const Tuple<String, int> actual = pfa(fb).value();
    auto expected = pure<StructApplicative>(Tuple{"nine", 5}).value();
    ASSERT_EQ(actual, expected);
}

TEST(Kernel_Ops_Product, is_reusable) {
    auto fa = pure<StructApplicative>(9);
    auto fb = pure<StructApplicative>(5);
    auto pfa = product(fa);
    ASSERT_EQ(pfa(fa).value(), pure<StructApplicative>(Tuple{9, 9}).value());
    ASSERT_EQ(pfa(fb).value(), pure<StructApplicative>(Tuple{9, 5}).value());
}
