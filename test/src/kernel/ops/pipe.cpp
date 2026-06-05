/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <string>

using namespace fp;
using namespace fp::laws;
using namespace fp::test;

TEST(Kernel_Ops_Pipe_Laws, usage) {
    auto liftedSquare = lift<StructFunctor>(square);
    auto program = pipe(
      identity,      // start with the value as-is
      liftedSquare,  // get value and uses ordinary square to lift result into F
      fmap(triple),  // transform inside F
      extract        // unwrap back to value
    );

    auto result = program(42);
    ASSERT_EQ(result, square(42) * 3);
}

RC_GTEST_PROP(Kernel_Ops_Pipe_Laws, left_identity, ()) {
    auto a = *rc::gen::arbitrary<int>();
    RC_ASSERT(PipeLaws::left_identity(square, a * a));
}

RC_GTEST_PROP(Kernel_Ops_Pipe_Laws, right_identity, ()) {
    auto a = *rc::gen::arbitrary<int>();
    RC_ASSERT(PipeLaws::right_identity(square, a * a));
}

RC_GTEST_PROP(Kernel_Ops_Pipe_Laws, associativity, ()) {
    auto i = *rc::gen::arbitrary<int>();
    RC_ASSERT(PipeLaws::associativity(square, triple, halve, i));
}

RC_GTEST_PROP(Kernel_Ops_Pipe_Laws, variadic_consistency, ()) {
    auto i = *rc::gen::arbitrary<int>();
    RC_ASSERT(PipeLaws::variadic(triple, halve, square, i));
}
