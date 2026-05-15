#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <string>

using namespace fp;
using namespace fp::syntax;
using namespace fp::test;

// individual operators

TEST(Syntax_Operators_Dollar, usage) {
    auto applied = square &= 10;
    auto expected = square(10);
    ASSERT_EQ(applied, expected);
}

TEST(Syntax_Operators_Pipe, usage) {
    auto piped = square | triple | halve;
    auto expected = pipe(square, triple, halve);
    ASSERT_EQ(piped(42), expected(42));
}

TEST(Syntax_Operators_Pipe, usage_with_dollar) {
    auto piped = square | triple | halve &= 42;
    auto expected = pipe(always(42), square, triple, halve)(any);
    ASSERT_EQ(piped, expected);
}
TEST(Syntax_Operators_Compose, usage) {
    auto composed = halve * triple * square;
    auto expected = compose(halve, triple, square);
    ASSERT_EQ(composed(42), expected(42));
}

TEST(Syntax_Operators_Compose, usage_with_dollar) {
    auto result = halve* triple* square &= 42;
    auto expected = compose(halve, triple, square)(42);
    ASSERT_EQ(result, expected);
}
