#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <concepts>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Mixins_WithFunctor, makes_functor_with_map) {
    static_assert(IsFunctor<StructFunctor>, "StructFunctor must be functor");
    static_assert(HasMap<StructFunctor<int>>, "StructFunctor<A> must have map");
}

TEST(Kernel_Mixins_WithFunctor, map_is_callable) {
    auto val = pure<StructFunctor>(42);
    EXPECT_EQ(42, val.map(identity).value());
}

TEST(Kernel_Mixins_WithFunctor, as_is_callable) {
    auto val = pure<StructFunctor>(42);
    ASSERT_EQ(val.as(String("hello")).value(), "hello");
}

TEST(Kernel_Mixins_WithFunctor, discard_is_callable) {
    auto val = pure<StructFunctor>(42);
    ASSERT_EQ(val.discard().value(), nothing);
}

TEST(Kernel_Mixins_WithFunctor, fproduct_is_callable) {
    auto val = pure<StructFunctor>(42);
    auto result = val.fproduct([](int x) -> int { return x * 2; });
    static_assert(
      std::same_as<decltype(result), StructFunctor<Tuple<int, int>>>
    );
    ASSERT_EQ(std::get<0>(result.value()), 42);
    ASSERT_EQ(std::get<1>(result.value()), 84);
}
