#include <fp/fp.h>
#include <gtest/gtest.h>

#include <concepts>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct : WithApply<TestStruct<A>> {};

// as returns a reusable arrow over any F<A>
TEST(Kernel_Ops_As, returns_arrow_over_functor) {
    auto asMisha = as(String("misha"));
    auto fa = pure<TestStruct>(42);
    auto fb = pure<TestStruct>(String("hello"));
    static_assert(std::same_as<decltype(asMisha(fa)), TestStruct<String>>);
    static_assert(std::same_as<decltype(asMisha(fb)), TestStruct<String>>);
    ASSERT_EQ(asMisha(fa).value(), "misha");
    ASSERT_EQ(asMisha(fb).value(), "misha");
}

// cast normalisation
TEST(Kernel_Ops_As, cstring_normalised_to_string) {
    auto asMisha = as("misha");
    auto fa = pure<TestStruct>(42);
    static_assert(std::same_as<decltype(asMisha(fa)), TestStruct<String>>);
    ASSERT_EQ(asMisha(fa).value(), String("misha"));
}
