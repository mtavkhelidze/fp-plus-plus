#include <fp/fp.h>
#include <gtest/gtest.h>

#include <concepts>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

// lift morphisms into F
TEST(Core_Functor, map_lifts_morphism_A_to_B_into_FA_to_FB) {
    auto fa = pure<TestStruct>(42);
    auto arrow = Functor<TestStruct>::map([](int x) { return x + 1; });
    // arrow is F<A> → F<B> — a reusable first-class value
    auto result1 = arrow(fa);
    auto result2 = arrow(fa);
    static_assert(std::same_as<decltype(result1), TestStruct<int>>);
    ASSERT_EQ(result1.value(), 43);
    // same arrow, same result — pure
    ASSERT_EQ(result2.value(), 43);
}

// identity law: map(fa, id) == fa
TEST(Core_Functor, law_identity) {
    auto fa = pure<TestStruct>(42);
    auto result = Functor<TestStruct>::map(id)(fa);
    ASSERT_EQ(result.value(), fa.value());
}

// composition law: map(map(fa, f), g) == map(fa, g ∘ f)
TEST(Core_Functor, law_composition) {
    auto fa = pure<TestStruct>(10);
    auto f = [](int x) { return x * 2; };
    auto g = [](int x) { return x + 3; };
    auto lhs = Functor<TestStruct>::map(g)(Functor<TestStruct>::map(f)(fa));
    auto rhs = Functor<TestStruct>::map([&](int x) { return g(f(x)); })(fa);
    ASSERT_EQ(lhs.value(), rhs.value());
}
