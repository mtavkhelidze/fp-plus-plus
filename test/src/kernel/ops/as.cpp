#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <concepts>

using namespace fp;
using namespace fp::test;

// as returns a reusable arrow over any F<A>
TEST(Kernel_Ops_As, returns_arrow_over_functor) {
    auto asMisha = as(String("misha"));
    auto fa = pure<StructWithPure>(42);
    auto fb = pure<StructWithPure>(String("hello"));
    static_assert(std::same_as<decltype(asMisha(fa)), StructWithPure<String>>);
    static_assert(std::same_as<decltype(asMisha(fb)), StructWithPure<String>>);
    ASSERT_EQ(asMisha(fa).value(), "misha");
    ASSERT_EQ(asMisha(fb).value(), "misha");
}

// cast normalisation
TEST(Kernel_Ops_As, cstring_normalised_to_string) {
    auto asMisha = as("misha");
    auto fa = pure<StructWithPure>(42);
    static_assert(std::same_as<decltype(asMisha(fa)), StructWithPure<String>>);
    ASSERT_EQ(asMisha(fa).value(), String("misha"));
}
