#include <fp/fp.h>
#include <gtest/gtest.h>

#include <concepts>
#include <functional>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

// Functor core

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

// Functor Laws

// identity: map(fa, id) == fa
TEST(Core_Functor, law_identity) {
    auto fa = pure<TestStruct>(42);
    auto result = Functor<TestStruct>::map(id)(fa);
    ASSERT_EQ(result.value(), fa.value());
}

// composition: map(map(fa, f), g) == map(fa, g ∘ f)
TEST(Core_Functor, law_composition) {
    auto fa = pure<TestStruct>(10);
    auto f = [](int x) { return x * 2; };
    auto g = [](int x) { return x + 3; };
    auto lhs = Functor<TestStruct>::map(g)(Functor<TestStruct>::map(f)(fa));
    auto rhs = Functor<TestStruct>::map([&](int x) { return g(f(x)); })(fa);
    ASSERT_EQ(lhs.value(), rhs.value());
}

// Change of type

TEST(Core_Functor, map_int_to_double) {
    auto fa = pure<TestStruct>(7);
    auto result =
      Functor<TestStruct>::map([](int x) -> double { return x * 1.5; })(fa);
    ASSERT_DOUBLE_EQ(result.value(), 10.5);
}

TEST(Core_Functor, map_string_to_int) {
    auto fa = pure<TestStruct>(String{"hello"});
    auto result = Functor<TestStruct>::map([](const String& s) {
        return static_cast<int>(s.size());
    })(fa);
    ASSERT_EQ(result.value(), 5);
}

// Casted types

// cast: const char* normalised to String
TEST(Core_Functor, map_int_to_cstring_normalised_to_string) {
    auto fa = pure<TestStruct>(42);
    auto result =
      Functor<TestStruct>::map([](int) -> const char* { return "hello"; })(fa);
    // cast<const char*> = String — result must be TestStruct<String>
    ASSERT_EQ(result.value(), String{"hello"});
}

// Callable types

int free_plus_one(int x) { return x + 1; }

TEST(Core_Functor, map_function_pointer) {
    auto fa = pure<TestStruct>(9);
    auto result = Functor<TestStruct>::map(free_plus_one)(fa);
    ASSERT_EQ(result.value(), 10);
}

TEST(Core_Functor, map_std_function) {
    auto fa = pure<TestStruct>(9);
    std::function<int(int)> f = [](int x) { return x * 3; };
    auto result = Functor<TestStruct>::map(f)(fa);
    ASSERT_EQ(result.value(), 27);
}

TEST(Core_Functor, map_generic_lambda) {
    auto fa = pure<TestStruct>(4);
    auto result = Functor<TestStruct>::map([](auto x) { return x * x; })(fa);
    ASSERT_EQ(result.value(), 16);
}

struct Square {
    int operator()(int x) const { return x * x; }
};

TEST(Core_Functor, map_callable_struct) {
    auto f = Square{};
    auto fa = pure<TestStruct>(4);
    auto result = Functor<TestStruct>::map(f)(fa);
    ASSERT_EQ(result.value(), 16);
}
