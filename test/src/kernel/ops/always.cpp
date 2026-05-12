#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;

TEST(Kernel_Ops_Always, returns_function_returning_captured_value) {
    auto forty_two = always(42);
    const auto result = forty_two(142);
    EXPECT_EQ(result, 42);
}

TEST(Kernel_Ops_Always, returns_function_which_ignores_argument_type) {
    auto forty_two = always(String("forty-two"));
    const auto result = forty_two(241);
    EXPECT_EQ(result, "forty-two");
}
