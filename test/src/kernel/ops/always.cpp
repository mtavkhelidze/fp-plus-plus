#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Ops_Always, composes_with_fmap) {
    auto fa = pure<StructWithPure>(42);
    auto result = fmap(always(String("hello")))(fa);
    //    static_assert(std::is_same_v<decltype(result),
    //    StructWithPure<String>>);
    ASSERT_EQ(result.value(), "hello");
}

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
