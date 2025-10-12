#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

TEST(Prelude_Pure, pure_int) {
    auto b = pure<TestStruct>(42);  // NOLINT
    static_assert(std::is_same_v<decltype(b), TestStruct<int>>);
    EXPECT_EQ(b.value(), 42);
}

TEST(Prelude_Pure, pure_string) {
    std::string s = "hello";
    auto b = pure<TestStruct>(s);
    static_assert(std::is_same_v<decltype(b), TestStruct<std::string>>);
    EXPECT_EQ(b.value(), "hello");
}

TEST(Prelude_Pure, pure_temp_string) {
    auto b = pure<TestStruct>(std::string("world"));
    EXPECT_EQ(b.value(), "world");
}
