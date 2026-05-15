#include <fp/fp.h>
#include <gtest/gtest.h>

#include <concepts>
#include <cstddef>
#include <string>

using namespace fp;
using namespace fp::syntax;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct
    : WithApply<TestStruct<A>>
    , WithFunctor<TestStruct<A>> {};

// individual operators

TEST(Syntax_Operators, pipe_left_to_right) {
    auto f = [](int x) -> int { return x + 1; };
    auto g = [](int x) -> int { return x * 2; };
    auto h = pipe(f, g);
    ASSERT_EQ((f | g) &= 42, h &= 42);  // (42+1)*2 = 86
    ASSERT_EQ((f | g) &= 42, 86);
}

TEST(Syntax_Operators, compose_right_to_left) {
    auto f = [](int x) -> int { return x + 1; };
    auto g = [](int x) -> int { return x * 2; };
    ASSERT_EQ((f * g) &= 42, 85);  // f(g(42)) = (42*2)+1 = 85
}

TEST(Syntax_Operators, apply_feeds_value) {
    auto f = [](int x) -> int { return x * 3; };
    ASSERT_EQ(f &= 10, 30);
}

// precedence — &= binds looser than | and *

TEST(Syntax_Operators, pipe_chain_then_apply) {
    auto f = [](int x) -> String { return std::to_string(x); };
    auto g = [](const String& s) -> String { return s + "!"; };
    auto h = [](const String& s) -> std::size_t { return s.size(); };
    ASSERT_EQ(f | g | h &= 42, 3);  // "42" + "!" = "42!" → size 3
}

TEST(Syntax_Operators, compose_chain_then_apply) {
    auto f = [](std::size_t x) -> std::size_t { return x * 2; };
    auto g = [](const String& s) -> std::size_t { return s.size(); };
    auto h = [](int x) -> String { return std::to_string(x); };
    ASSERT_EQ(f* g* h &= 42, 4);  // h(42)="42" → g="2" → f=4
}

// with functor ops

TEST(Syntax_Operators, fmap_in_pipeline) {
    auto fa = pure<TestStruct>(42);
    auto result = fmap([](int x) -> int { return x + 1; }) &= fa;
    ASSERT_EQ(result.value(), 43);
}

TEST(Syntax_Operators, functor_pipeline) {
    auto result = pure<TestStruct, int> | as("hello") | discard;
    static_assert(std::same_as<decltype(result(10)), TestStruct<Nothing>>);
    ASSERT_EQ(result(10).value(), nothing);
}
