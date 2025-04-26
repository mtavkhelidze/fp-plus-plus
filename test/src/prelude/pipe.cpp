#include <fp/operators/composition.h>
#include <fp/prelude/identity.h>
#include <gtest/gtest.h>

#include "shorts.h"

using namespace fp::test;
using namespace fp::operators::composition;
using namespace fp::prelude;

// like | in Haskell
TEST(Prelude_Pipe_Operator, is_reverse_of_compose) {
    auto initial = 2;
    auto f = increment * triple;
    auto g = triple | increment;
    auto actual_f = f(initial);
    auto actual_g = g(initial);

    EXPECT_EQ(actual_f, actual_g);
}

TEST(Prelude_Pipe_Operator, works_with_multiple_chained_functions) {
    auto initial = 2;
    auto increment = [](int x) { return x + 1; };
    auto triple = [](int x) { return x * 3; };
    auto square = [](int x) { return x * x; };

    auto piped = increment | triple | square;
    auto composed = square * triple * increment;

    auto result_p = piped(initial);
    auto result_c = composed(initial);

    EXPECT_EQ(result_p, result_c);
}
