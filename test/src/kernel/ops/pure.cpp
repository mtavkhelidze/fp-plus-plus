#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <type_traits>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Ops_Pure, trivial_int) {
    auto b = pure<StructApply>(42);
    static_assert(std::is_same_v<decltype(b), StructApply<int>>);
    EXPECT_EQ(b.value(), 42);
}

TEST(Kernel_Ops_Pure, trivial_string) {
    String s = "hello";
    auto b = pure<StructApply>(s);
    static_assert(std::is_same_v<decltype(b), StructApply<String>>);
    EXPECT_EQ(b.value(), "hello");
}

TEST(Kernel_Ops_Pure, temp_string) {
    auto b = pure<StructApply>(String("world"));
    EXPECT_EQ(b.value(), "world");
}
TEST(Kernel_Ops_Pure, const_ref) {
    const int x = 42;
    auto b = pure<StructApply>(x);
    static_assert(std::is_same_v<decltype(b), StructApply<int>>);
    EXPECT_EQ(b.value(), 42);
}

TEST(Kernel_Ops_Pure, nothing) {
    auto b = pure<StructApply>(nothing);
    static_assert(std::is_same_v<decltype(b), StructApply<Nothing>>);
    EXPECT_EQ(b.value(), nothing);
}

TEST(Kernel_Ops_Pure, any) {
    Any<int> a = any;
    auto b = pure<StructApply>(a);
    static_assert(std::is_same_v<decltype(b), StructApply<Any<int>>>);
    EXPECT_EQ(b.value(), any);
}

TEST(Kernel_Ops_Pure, string_literal) {
    auto b = pure<StructApply>("hello");
    static_assert(std::is_same_v<decltype(b), StructApply<String>>);
    EXPECT_EQ(b.value(), "hello");
}
