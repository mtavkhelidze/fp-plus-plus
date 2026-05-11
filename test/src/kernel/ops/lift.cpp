#include <fp/fp.h>
#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <type_traits>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

TEST(Kernel_Ops_Lift, simple_lambda) {
    auto doubleFn = lift<TestStruct>([](int x) { return x * 2; });
    auto result = doubleFn(21);
    static_assert(std::is_same_v<decltype(result), TestStruct<int>>);
    EXPECT_EQ(result.value(), 42);
}

TEST(Kernel_Ops_Lift, identity) {
    auto idFn = lift<TestStruct>([](int x) { return x; });
    auto result = idFn(10);
    EXPECT_EQ(result.value(), 10);
}

TEST(Kernel_Ops_Lift, string_length) {
    auto lenFn =
      lift<TestStruct>([](const std::string_view& s) { return s.length(); });
    auto result = lenFn(String("hello"));
    EXPECT_EQ(result.value(), 5);
}

TEST(Kernel_Ops_Lift, type_change) {
    // A -> B where A != B
    auto toStringFn = lift<TestStruct>([](int x) { return std::to_string(x); });
    auto result = toStringFn(42);
    static_assert(std::is_same_v<decltype(result), TestStruct<String>>);
    EXPECT_EQ(result.value(), "42");
}

TEST(Kernel_Ops_Lift, nothing_result) {
    auto toNothing = lift<TestStruct>([](int) { return nothing; });
    auto result = toNothing(42);
    static_assert(std::is_same_v<decltype(result), TestStruct<Nothing>>);
    EXPECT_EQ(result.value(), nothing);
}

TEST(Kernel_Ops_Lift, lift_is_reusable) {
    auto doubleFn = lift<TestStruct>([](int x) { return x * 2; });
    EXPECT_EQ(doubleFn(1).value(), 2);
    EXPECT_EQ(doubleFn(2).value(), 4);
    EXPECT_EQ(doubleFn(21).value(), 42);
}

TEST(Kernel_Ops_Lift, function_pointer) {
    auto fn =
      lift<TestStruct>(static_cast<int (*)(int)>([](int x) { return x + 1; }));
    auto result = fn(41);
    static_assert(std::is_same_v<decltype(result), TestStruct<int>>);
    EXPECT_EQ(result.value(), 42);
}
