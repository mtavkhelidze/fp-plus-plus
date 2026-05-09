#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

TEST(Kernel_Ops_Pure, trivial_int) {
    auto b = pure<TestStruct>(42);
    static_assert(std::is_same_v<decltype(b), TestStruct<int>>);
    EXPECT_EQ(b.value(), 42);
}

TEST(Kernel_Ops_Pure, trivial_string) {
    std::string s = "hello";
    auto b = pure<TestStruct>(s);
    static_assert(std::is_same_v<decltype(b), TestStruct<std::string>>);
    EXPECT_EQ(b.value(), "hello");
}

TEST(Kernel_Ops_Pure, temp_string) {
    auto b = pure<TestStruct>(std::string("world"));
    EXPECT_EQ(b.value(), "world");
}
TEST(Kernel_Ops_Pure, const_ref) {
    const int x = 42;
    auto b = pure<TestStruct>(x);
    static_assert(std::is_same_v<decltype(b), TestStruct<int>>);
    EXPECT_EQ(b.value(), 42);
}

TEST(Kernel_Ops_Pure, nothing) {
    auto b = pure<TestStruct>(nothing);
    static_assert(std::is_same_v<decltype(b), TestStruct<Nothing>>);
    EXPECT_EQ(b.value(), nothing);
}

TEST(Kernel_Ops_Pure, any) {
    Any<int> a = any;
    auto b = pure<TestStruct>(a);
    static_assert(std::is_same_v<decltype(b), TestStruct<Any<int>>>);
    EXPECT_EQ(b.value(), any);
}

TEST(Kernel_Ops_Pure, string_literal) {
    auto b = pure<TestStruct>("hello");
    static_assert(std::is_same_v<decltype(b), TestStruct<std::string>>);
    EXPECT_EQ(b.value(), "hello");
}
