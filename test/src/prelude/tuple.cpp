#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp::prelude;
TEST(Prelude_Tuple, Tuple) {
    auto t = fp::tuple(1, 2);
    EXPECT_EQ(fp::first(t), 1);
    EXPECT_EQ(fp::second(t), 2);
}

TEST(Prelude_Tuple, TupleWithString) {
    std::string s = "hello";
    const char* c = "world";
    auto t = fp::tuple(s, c);
    EXPECT_EQ(fp::first(t), s);
    EXPECT_STREQ(fp::second(t), c);
}
