#include <fp/fp.h>
#include <gtest/gtest.h>

#include "functor_types.h"

using namespace fp;
using namespace fp::traits;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

TEST(Functor_Props, identity) {  //
    auto fa = pure<FunctorStruct>(42);
    auto fb = Functor::map(fa)(identity);
    ASSERT_TRUE(fa.is_stack());
    ASSERT_TRUE(fb.is_stack());
    ASSERT_EQ(fb.value(), fa.value());
}

// NOLINTEND(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
