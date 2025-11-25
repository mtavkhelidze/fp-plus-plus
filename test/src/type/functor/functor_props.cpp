#include <fp/fp.h>
#include <gtest/gtest.h>

#include "functor_types.h"

using namespace fp;
using namespace fp::traits;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

static auto tr(int x) -> std::string { return std::to_string(x); }

TEST(Functor_Props, identity) {  //
    auto fa = pure<FunctorStruct>(42);
    auto fb = Functor::map(fa)(identity);
    ASSERT_EQ(fb.value(), 42);
}

// NOLINTEND(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
