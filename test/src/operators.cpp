// NOLINTBEGIN:-hicpp-named-parameter,-readability-named-parameter,llvmlibc-implementation-in-namespace

#include <fp/fp.h>
#include <gtest/gtest.h>

#include "shorts.h"

using namespace fp;
using namespace fp::test;
using namespace fp::operators::all;

// >= like |> in Elm
TEST(Syntax_Operator_Pipe, applies_function) { EXPECT_EQ(42 >= increment, 43); }

TEST(Syntax_Operator_Pipe, works_with_lambdas) { EXPECT_EQ(4 >= square, 16); }

TEST(Syntax_Operator_Pipe, supports_chaining) {
    EXPECT_EQ(10 >= triple >= int_to_string, "30");
}

TEST(Syntax_Operator_Pipe, works_with_void_functions) {
    std::stringstream ss;
    auto print = [&](int x) { ss << x; };

    5 >= print;
    EXPECT_EQ(ss.str(), "5");
}
// NOLINTEND
