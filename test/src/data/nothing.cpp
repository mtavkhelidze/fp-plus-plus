#include <fp/fp.h>
#include <gtest/gtest.h>

#include <compare>
#include <sstream>
#include <type_traits>

using namespace fp;

TEST(Nothing, all_instances_are_equal) {
    // Two independently constructed Nothing values are identical
    constexpr Nothing a{};
    constexpr Nothing b{};
    static_assert(a == b);
    static_assert(a == nothing);
    static_assert(b == nothing);
}

TEST(Nothing, is_a_unit_type) {
    // Nothing carries no information — there is only one possible value
    static_assert(nothing == nothing);
    static_assert(!(nothing != nothing));
}

TEST(Nothing, is_ordered) {
    // Nothing is always equal to itself in any ordering
    static_assert((nothing <=> nothing) == std::strong_ordering::equal);
}

TEST(Nothing, is_printable) {
    // Nothing prints as "Nothing"
    EXPECT_EQ(nothing.to_string(), "Nothing");
}

TEST(Nothing, works_with_ostream) {
    std::ostringstream os;
    os << nothing;
    EXPECT_EQ(os.str(), "Nothing");
}

TEST(Nothing, is_constexpr) {
    // Nothing is fully usable at compile time
    constexpr Nothing n = nothing;
    static_assert(n == nothing);
}

TEST(Whatever, is_an_alias_for_nothing) {
    // Whatever is a placeholder when the type does not matter
    constexpr Whatever w = whatever;
    static_assert(w == nothing);
    static_assert(std::is_same_v<Whatever, Nothing>);
}

TEST(Any, is_a_placeholder_type_constructor) {
    // Any<A> collapses any type to Nothing
    // useful in declarations and tests where the type does not matter
    static_assert(std::is_same_v<Any<int>, Nothing>);
    static_assert(std::is_same_v<Any<int, String>, Nothing>);
    static_assert(std::is_same_v<Any<>, Nothing>);
    constexpr Any<int> a = any;
    static_assert(a == nothing);
}
