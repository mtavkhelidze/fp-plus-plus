#include <fp/fp.h>
#include <gtest/gtest.h>

#include "value_types.h"

using namespace fp;

TEST(Prelude_Pure, pure_int) {
    auto b = pure<ValueStruct>(42);  // NOLINT
    static_assert(std::is_same_v<decltype(b), ValueStruct<int>>);
    EXPECT_EQ(b.value(), 42);
}

TEST(Prelude_Pure, pure_string) {
    std::string s = "hello";
    auto b = pure<ValueStruct>(s);
    static_assert(std::is_same_v<decltype(b), ValueStruct<std::string>>);
    EXPECT_EQ(b.value(), "hello");
}

TEST(Prelude_Pure, pure_temp_string) {
    auto b = pure<ValueStruct>(std::string("world"));
    EXPECT_EQ(b.value(), "world");
}
