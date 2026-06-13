/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::test;
using namespace fp::internal::meta::arrow;

TEST(Internal_Meta_Arrow, recognises_a_to_b) {
    auto f = [](int x) -> double { return x * 2.0; };
    static_assert(fp::internal::meta::arrow::is_arrow<decltype(f), int>);
}

TEST(Internal_Meta_Arrow, rejects_wrong_argument_type) {
    auto f = [](String x /* NOLINT */) -> int { return x.size(); };
    static_assert(!fp::internal::meta::arrow::is_arrow<decltype(f), int>);
}

TEST(Internal_Meta_Arrow, rejects_void_return) {
    auto f = [](int /* _*/) -> void {};
    static_assert(!fp::internal::meta::arrow::is_arrow<decltype(f), int>);
}

TEST(Internal_Meta_Arrow, recognises_nested_container_as_value) {
    using FA = fp::test::StructFunctor<int>;
    auto f = [](FA /* NOLINT*/) -> String { return "x"; };
    static_assert(fp::internal::meta::arrow::is_arrow<decltype(f), FA>);
}

TEST(Internal_Meta_Arrow, rejects_unwrapped_arg_against_wrapped_type) {
    using FA = fp::test::StructFunctor<int>;
    auto f = [](int /* _*/) -> String { return "x"; };
    static_assert(!fp::internal::meta::arrow::is_arrow<decltype(f), FA>);
}

TEST(Internal_Meta_Arrow, recognises_a_b_c) {
    auto f = [](int x) -> auto {
        return [x](String s /* NOLINT */) -> double { return x + s.size(); };
    };
    static_assert(
      fp::internal::meta::arrow::is_sparrow<decltype(f), int, String>
    );
}

TEST(Internal_Meta_Arrow, rejects_unary_as_sparrow) {
    auto f = [](int x) -> double { return x * 2.0; };
    static_assert(
      !fp::internal::meta::arrow::is_sparrow<decltype(f), int, String>
    );
}
