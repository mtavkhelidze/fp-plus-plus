#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <concepts>
#include <string>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Mixins_WithApplicative, makes_applicative_with_ap) {
    static_assert(
      IsApplicative<StructApplicative>, "WithApplicative must be applicative"
    );
    static_assert(
      HasAp<StructApplicative<Unit>>, "WithApplicative<A> must have .ap"
    );
}

TEST(Kernel_Mixins_WithApplicative_Ap, is_callable) {
    auto fa = pure<StructApplicative>(42);
    auto ff = pure<StructApplicative>(triple);
    ASSERT_EQ(fa.ap(ff).value(), 42 * 3);
}

TEST(Kernel_Mixins_WithApplicative_Map2, combines_two_containers) {
    auto fa = pure<StructApplicative>(10);
    auto fb = pure<StructApplicative>(32);
    auto adder = fa.map2([](int a) -> auto {
        return [a](int b) -> auto { return a + b; };
    });
    ASSERT_EQ(adder(fb).value(), 42);
}

TEST(Kernel_Mixins_WithApplicative_Map2, partial_application_is_reusable) {
    auto fa = pure<StructApplicative>(10);
    auto adder = fa.map2([](int a) -> auto {
        return [a](int b) -> auto { return a + b; };
    });
    ASSERT_EQ(adder(pure<StructApplicative>(1)).value(), 11);
    ASSERT_EQ(adder(pure<StructApplicative>(2)).value(), 12);
}

TEST(Kernel_Mixins_WithApplicative_Map2, combines_different_types) {
    auto fa = pure<StructApplicative>(42);
    auto ffa = fa.map2([](int a) -> auto {
        return [a](const String& b) -> auto { return b + std::to_string(a); };
    });
    auto fb = pure<StructApplicative>(String("hello"));
    auto result = ffa(fb);
    static_assert(std::same_as<decltype(result), StructApplicative<String>>);
    ASSERT_EQ(result.value(), "hello42");
}
