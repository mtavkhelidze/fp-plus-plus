/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::internal::meta::rebind;
using namespace fp::kernel::mixins;
using namespace fp::test;

template <typename A>
struct StructA {};

template <typename B>
struct StructB {};

TEST(Internal_Meta_rebind, is_same_f_generic_struct) {
    static_assert(is_same_f<StructA<int>, StructA<String>>);
    static_assert(!is_same_f<StructA<int>, StructB<int>>);
    static_assert(is_same_f<StructA<int>, StructA<int>>);  // trivially same
}

TEST(Internal_Meta_rebind, is_same_f_mixedin_struct) {
    static_assert(is_same_f<StructWithPure<int>, StructWithPure<String>>);
    static_assert(!is_same_f<StructWithPure<int>, StructFunctor<int>>);
}
