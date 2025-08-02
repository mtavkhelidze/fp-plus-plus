#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp::prelude;
TEST(Prelude_Tuple, Tuple) {
    auto t = fp::tuple(1, 2);
    EXPECT_EQ(fp::get<0>(t), 1);
    EXPECT_EQ(fp::get<1>(t), 2);
    EXPECT_EQ(fp::get<2>(t), 3);
}
