#include <fp/fp.h>
#include <gtest/gtest.h>

#include <functional>
#include <string>
#include <type_traits>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

// core
TEST(Kernel_Ops_Fmap, returns_reusable_arrow) {
    auto arrow = fmap([](int x) { return x + 1; });
    auto fa = pure<TestStruct>(42);
    ASSERT_EQ(arrow(fa).value(), 43);
    ASSERT_EQ(arrow(fa).value(), 43);  // reuse
}

// Type juggling

TEST(Kernel_Ops_Fmap, int_to_string) {
    auto fa = pure<TestStruct>(99);
    auto result = fmap([](int x) { return std::to_string(x); })(fa);
    static_assert(std::is_same_v<decltype(result), TestStruct<String>>);
    ASSERT_EQ(result.value(), "99");
}

// cast normalisation
TEST(Kernel_Ops_Fmap, cstring_normalised_to_string) {
    auto fa = pure<TestStruct>(42);
    auto result = fmap([](int) -> const char* { return "hello"; })(fa);
    static_assert(std::is_same_v<decltype(result), TestStruct<String>>);
    ASSERT_EQ(result.value(), String("hello"));
}
TEST(Kernel_Ops_Fmap, int_to_double) {
    auto fa = pure<TestStruct>(7);
    auto result = fmap([](int x) -> double { return x * 1.5; })(fa);
    ASSERT_DOUBLE_EQ(result.value(), 10.5);
}

TEST(Kernel_Ops_Fmap, string_to_int) {
    auto fa = pure<TestStruct>(String{"hello"});
    auto result =
      fmap([](const String& s) { return static_cast<int>(s.size()); })(fa);
    ASSERT_EQ(result.value(), 5);
}

// call surface
static auto free_plus_one(int x) -> int { return x + 1; }

TEST(Kernel_Ops_Fmap, normal_function) {
    auto fa = pure<TestStruct>(9);
    auto result = fmap(free_plus_one)(fa);
    ASSERT_EQ(result.value(), 10);
}

TEST(Kernel_Ops_Fmap, std_function) {
    std::function<int(int)> f = [](int x) -> int { return x * 3; };
    auto fa = pure<TestStruct>(9);
    auto result = fmap(f)(fa);
    ASSERT_EQ(result.value(), 27);
}

TEST(Kernel_Ops_Fmap, generic_lambda) {
    auto fa = pure<TestStruct>(4);
    auto result = fmap([](auto x) -> auto { return x * x; })(fa);
    ASSERT_EQ(result.value(), 16);
}

struct Square {
    auto operator()(int x) const -> int { return x * x; }
};

TEST(Kernel_Ops_Fmap, callable_struct) {
    auto f = Square{};
    auto fa = pure<TestStruct>(4);
    auto result = fmap(f)(fa);
    ASSERT_EQ(result.value(), 16);
}
