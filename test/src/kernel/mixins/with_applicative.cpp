#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::test;

TEST(Kernel_Mixins_WithApplicative, makes_applicative_with_ap) {
    static_assert(
      IsApplicative<StructApplicative>, "WithApplicative must be applicative"
    );
    static_assert(
      HasAp<StructApplicative<Any<>>>, "WithApplicative<A> must have .ap"
    );
}

TEST(Kernel_Mixins_WithApplicative_Ap, is_callable) {
    auto fa = pure<StructApplicative>(42);
    auto ff = pure<StructApplicative>(triple);
    ASSERT_EQ(fa.ap(ff).value(), 42 * 3);
}
