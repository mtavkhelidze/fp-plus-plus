#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <concepts>
#include <string>

using namespace fp;
using namespace fp::test;

// fproduct pairs value with result of f
TEST(Kernel_Ops_Fproduct, pairs_value_with_result) {
    auto fa = pure<StructWithPure>(42);
    auto result = fproduct([](int x) -> int { return x * 2; })(fa);
    static_assert(
      std::same_as<decltype(result), StructWithPure<Tuple<int, int>>>
    );
    ASSERT_EQ(std::get<0>(result.value()), 42);
    ASSERT_EQ(std::get<1>(result.value()), 84);
}

// type change — B different from A
TEST(Kernel_Ops_Fproduct, pairs_with_different_type) {
    auto fa = pure<StructWithPure>(42);
    auto result =
      fproduct([](int x) -> String { return std::to_string(x); })(fa);
    static_assert(
      std::same_as<decltype(result), StructWithPure<Tuple<int, String>>>
    );
    ASSERT_EQ(std::get<0>(result.value()), 42);
    ASSERT_EQ(std::get<1>(result.value()), "42");
}

// cast normalisation — const char* → String
TEST(Kernel_Ops_Fproduct, cstring_normalised_to_string) {
    auto fa = pure<StructWithPure>(42);
    auto result = fproduct([](int) -> const char* { return "hello"; })(fa);
    static_assert(
      std::same_as<decltype(result), StructWithPure<Tuple<int, String>>>
    );
    ASSERT_EQ(std::get<0>(result.value()), 42);
    ASSERT_EQ(std::get<1>(result.value()), String("hello"));
}

// reusable arrow
TEST(Kernel_Ops_Fproduct, returns_reusable_arrow) {
    auto arrow = fproduct([](int x) -> int { return x * 2; });
    auto fa = pure<StructWithPure>(42);
    ASSERT_EQ(std::get<0>(arrow(fa).value()), 42);
    ASSERT_EQ(std::get<0>(arrow(fa).value()), 42);
}
