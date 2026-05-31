#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <type_traits>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Ops_Pure, trivial_int) {
    auto b = pure<StructWithPure>(42);
    static_assert(std::is_same_v<decltype(b), StructWithPure<int>>);
    EXPECT_EQ(b.value(), 42);
}

TEST(Kernel_Ops_Pure, trivial_string) {
    String s = "hello";
    auto b = pure<StructWithPure>(s);
    static_assert(std::is_same_v<decltype(b), StructWithPure<String>>);
    EXPECT_EQ(b.value(), "hello");
}

TEST(Kernel_Ops_Pure, temp_string) {
    auto b = pure<StructWithPure>(String("world"));
    EXPECT_EQ(b.value(), "world");
}
TEST(Kernel_Ops_Pure, const_ref) {
    const int x = 42;
    auto b = pure<StructWithPure>(x);
    static_assert(std::is_same_v<decltype(b), StructWithPure<int>>);
    EXPECT_EQ(b.value(), 42);
}

TEST(Kernel_Ops_Pure, unit_whatever) {
    auto b = pure<StructWithPure>(whatever);
    static_assert(std::is_same_v<decltype(b), StructWithPure<Unit>>);
    EXPECT_EQ(b.value(), whatever);
}

TEST(Kernel_Ops_Pure, string_literal) {
    auto b = pure<StructWithPure>("hello");
    static_assert(std::is_same_v<decltype(b), StructWithPure<String>>);
    EXPECT_EQ(b.value(), "hello");
}
