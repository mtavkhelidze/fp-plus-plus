#include <fp/fp.h>
#include <gtest/gtest.h>

#include "value_test.h"

using namespace fp;

TEST(Prelude_Lift, lift_double) {
    auto doubleFn = lift<ValueStruct>([](int x) { return x * 2; });
    auto result = doubleFn(21);  // NOLINT
    static_assert(std::is_same_v<decltype(result), ValueStruct<int>>);
    EXPECT_EQ(result.value(), 42);
}

TEST(Prelude_Lift, lift_identity) {
    auto idFn = lift<ValueStruct>([](int x) { return x; });
    auto result = idFn(10);  // NOLINT
    EXPECT_EQ(result.value(), 10);
}

TEST(Prelude_Lift, lift_string_length) {
    auto lenFn =
      lift<ValueStruct>([](const std::string& s) { return s.length(); });
    auto result = lenFn(std::string("hello"));
    EXPECT_EQ(result.value(), 5);
}
