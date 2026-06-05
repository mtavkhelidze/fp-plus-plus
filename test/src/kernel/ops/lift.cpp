/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <string_view>
#include <type_traits>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Ops_Lift, simple_lambda) {
    auto doubleFn = lift<StructWithPure>([](int x) { return x * 2; });
    auto result = doubleFn(21);
    static_assert(std::is_same_v<decltype(result), StructWithPure<int>>);
    EXPECT_EQ(result.value(), 42);
}

TEST(Kernel_Ops_Lift, identity) {
    auto idFn = lift<StructWithPure>([](int x) { return x; });
    auto result = idFn(10);
    EXPECT_EQ(result.value(), 10);
}

TEST(Kernel_Ops_Lift, string_length) {
    auto lenFn = lift<StructWithPure>([](const std::string_view& s) -> size_t {
        return s.length();
    });
    auto result = lenFn(String("hello"));
    EXPECT_EQ(result.value(), 5);
}

TEST(Kernel_Ops_Lift, type_change) {
    auto toStringFn =
      lift<StructWithPure>([](int x) -> String { return std::to_string(x); });
    auto result = toStringFn(42);
    static_assert(std::is_same_v<decltype(result), StructWithPure<String>>);
    EXPECT_EQ(result.value(), "42");
}

TEST(Kernel_Ops_Lift, cast_type_change) {
    auto toStringFn = lift<StructWithPure>([](int /*x*/) -> const char* {
        return "const char*";
    });
    auto result = toStringFn(42);
    static_assert(std::is_same_v<decltype(result), StructWithPure<String>>);
    EXPECT_EQ(result.value(), "const char*");
}

TEST(Kernel_Ops_Lift, unit_result) {
    auto toUnit = lift<StructWithPure>([](int) -> Unit { return whatever; });
    auto result = toUnit(42);
    static_assert(std::is_same_v<decltype(result), StructWithPure<Unit>>);
    EXPECT_EQ(result.value(), whatever);
}

TEST(Kernel_Ops_Lift, lift_is_reusable) {
    auto doubleFn = lift<StructWithPure>([](int x) -> int { return x * 2; });
    EXPECT_EQ(doubleFn(1).value(), 2);
    EXPECT_EQ(doubleFn(2).value(), 4);
    EXPECT_EQ(doubleFn(21).value(), 42);
}

TEST(Kernel_Ops_Lift, function_pointer) {
    auto fn = lift<StructWithPure>(static_cast<int (*)(int)>([](int x) -> int {
        return x + 1;
    }));
    auto result = fn(41);
    static_assert(std::is_same_v<decltype(result), StructWithPure<int>>);
    EXPECT_EQ(result.value(), 42);
}
