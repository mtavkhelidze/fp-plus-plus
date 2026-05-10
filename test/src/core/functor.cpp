#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

// Functor Laws

// identity: map(fa, id) == fa
TEST(Core_Functor, law_identity) {
    auto fa = pure<TestStruct>(42);
    auto result = Functor<TestStruct>::map(fa, id);
    ASSERT_EQ(result.value(), fa.value());
}

// composition: map(map(fa, f), g) == map(fa, g ∘ f)
TEST(Core_Functor, law_composition) {
    auto fa = pure<TestStruct>(10);
    auto f = [](int x) { return x * 2; };
    auto g = [](int x) { return x + 3; };
    auto lhs = Functor<TestStruct>::map(Functor<TestStruct>::map(fa, f), g);
    auto rhs = Functor<TestStruct>::map(fa, [&](int x) { return g(f(x)); });
    ASSERT_EQ(lhs.value(), rhs.value());
}

// Change of type

TEST(Core_Functor, map_int_to_double) {
    auto fa = pure<TestStruct>(7);
    auto result =
      Functor<TestStruct>::map(fa, [](int x) -> double { return x * 1.5; });
    ASSERT_DOUBLE_EQ(result.value(), 10.5);
}

TEST(Core_Functor, map_string_to_int) {
    auto fa = pure<TestStruct>(std::string{"hello"});
    auto result = Functor<TestStruct>::map(fa, [](const std::string& s) {
        return static_cast<int>(s.size());
    });
    ASSERT_EQ(result.value(), 5);
}

// Casted types

// cast: const char* normalised to std::string
TEST(Core_Functor, map_int_to_cstring_normalised_to_string) {
    auto fa = pure<TestStruct>(42);
    auto result =
      Functor<TestStruct>::map(fa, [](int) -> const char* { return "hello"; });
    // cast<const char*> = std::string — result must be TestStruct<std::string>
    ASSERT_EQ(result.value(), std::string{"hello"});
}

// Callable types

int free_plus_one(int x) { return x + 1; }

TEST(Core_Functor, map_function_pointer) {
    auto fa = pure<TestStruct>(9);
    auto result = Functor<TestStruct>::map(fa, free_plus_one);
    ASSERT_EQ(result.value(), 10);
}

TEST(Core_Functor, map_std_function) {
    auto fa = pure<TestStruct>(9);
    std::function<int(int)> f = [](int x) { return x * 3; };
    auto result = Functor<TestStruct>::map(fa, f);
    ASSERT_EQ(result.value(), 27);
}

TEST(Core_Functor, map_generic_lambda) {
    auto fa = pure<TestStruct>(4);
    auto result = Functor<TestStruct>::map(fa, [](auto x) { return x * x; });
    ASSERT_EQ(result.value(), 16);
}

struct Square {
    int operator()(int x) const { return x * x; }
};

TEST(Core_Functor, map_callable_struct) {
    auto fn = Square{};
    auto fa = pure<TestStruct>(4);
    auto result = Functor<TestStruct>::map(fa, fn);
    ASSERT_EQ(result.value(), 16);
}
