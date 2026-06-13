/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Ops_Fish, composes_two_lifter_functions) {
    auto ffn = lift<StructWithPure>(triple);
    auto ffg = lift<StructWithPure>(square);
    auto fished = fish(ffn)(ffg);
    auto result = fished(2);
    EXPECT_EQ(extract(result), 2 * 3 * (2 * 3));
}
