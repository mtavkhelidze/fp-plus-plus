#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <iostream>
#include <string>

using namespace fp;
using namespace fp::laws;
using namespace fp::test;

TEST(Kernel_Ops_Compose, usage) {
    auto program = compose(
      fmap(
        withId(42)
      ),         // F<Tuple<int, String>> -> F<Tuple<int,Tuple<int, String>>>
      identity,  // F<Tuple<int, String>> -> F<Tuple<int, String>>
      fproduct(formatPrice),  // F<int> -> F<Tuple<int, String>>
      fmap(square),           // F<int> -> F<int>
      pure<StructApply, int>  // int -> F<int>
    );

    auto result = program(200);  // run N cents
    auto [id, pair] = result.value();
    auto [cents, formatted] = pair;
    ASSERT_EQ(id, 42);
    ASSERT_EQ(cents, 40000);
    ASSERT_EQ(formatted, String("$400.0"));
}

RC_GTEST_PROP(Kernel_Ops_Compose_Laws, left_identity, ()) {
    auto a = *rc::gen::arbitrary<int>();
    RC_ASSERT(ComposeLaws::left_identity(square, a * a));
}

RC_GTEST_PROP(Kernel_Ops_Compose_Laws, right_identity, ()) {
    auto a = *rc::gen::arbitrary<int>();
    RC_ASSERT(ComposeLaws::right_identity(square, a * a));
}

RC_GTEST_PROP(Kernel_Ops_Compose_Laws, associativity, ()) {
    auto i = *rc::gen::arbitrary<int>();
    RC_ASSERT(ComposeLaws::associativity(withId(42), formatPrice, square, i));
}

RC_GTEST_PROP(Kernel_Ops_Compose_Laws, variadic_consistency, ()) {
    auto i = *rc::gen::arbitrary<int>();
    RC_ASSERT(ComposeLaws::variadic(withId(42), formatPrice, square, i));
}
