#include <fp/mixins/value.h>
#include <fp/prelude/lift.h>
#include <fp/prelude/pure.h>
#include <gtest/gtest.h>

using namespace fp::prelude;
using namespace fp::mixins::value;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

TEST(Prelude_Lift, lift_double) {
    auto doubleFn = lift<TestStruct>([](int x) { return x * 2; });
    auto result = doubleFn(21);
    static_assert(std::is_same_v<decltype(result), TestStruct<int>>);
    EXPECT_EQ(result.value(), 42);
}

TEST(Prelude_Lift, lift_identity) {
    auto idFn = lift<TestStruct>([](int x) { return x; });
    auto result = idFn(10);
    EXPECT_EQ(result.value(), 10);
}

TEST(Prelude_Lift, lift_string_length) {
    auto lenFn =
      lift<TestStruct>([](const std::string& s) { return s.length(); });
    auto result = lenFn(std::string("hello"));
    EXPECT_EQ(result.value(), 5);
}
