/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Ops_AndThen, returns_chooses_second) {
    auto fa = pure<StructApplicative>(12);
    auto fb = pure<StructApplicative>(String("hello"));
    auto then = andThen(fa);
    auto result = then(fb);
    EXPECT_EQ(extract(result), "hello");
}

// reusability — same `then`, different fb
TEST(Kernel_Ops_AndThen, is_reusable) {
    auto fa = pure<StructApplicative>(12);
    auto then = andThen(fa);
    EXPECT_EQ(extract(then(pure<StructApplicative>(1))), 1);
    EXPECT_EQ(extract(then(pure<StructApplicative>(2))), 2);
}

TEST(Kernel_Ops_Before, returns_first) {
    auto fa = pure<StructApplicative>(12);
    auto fb = pure<StructApplicative>(String("hello"));
    auto result = before(fa)(fb);
    EXPECT_EQ(extract(result), 12);
}

TEST(Kernel_Ops_Before, is_reusable) {
    auto fa = pure<StructApplicative>(12);
    auto bef = before(fa);
    EXPECT_EQ(extract(bef(pure<StructApplicative>(1))), 12);
    EXPECT_EQ(extract(bef(pure<StructApplicative>(2))), 12);
}
