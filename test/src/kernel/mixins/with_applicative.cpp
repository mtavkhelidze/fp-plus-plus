#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Mixins_WithApplicative, makes_applicative_with_ap) {
    static_assert(
      IsApplicative<StructApplicative>, "StructFunctor must be a functor"
    );
    static_assert(
      HasAp<StructApplicative<Any<>>>, "StructFunctor must be a functor"
    );
}

TEST(Kernel_Mixins_WithApplicative, ap_is_callable) {
    auto fa = pure<StructApplicative>(42);
    auto ff = pure<StructApplicative>(triple);
    ASSERT_EQ(fa.ap(ff).value(), 42 * 3);
}
