#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <concepts>
#include <string>

using namespace fp;
using namespace fp::test;

// core — combines two containers with a curried binary function
TEST(Kernel_Ops_Map2, combines_two_containers) {
    auto fa = pure<StructWithPure>(10);
    auto fb = pure<StructWithPure>(32);
    auto result = map2([](int a) -> auto {
        return [a](int b) -> auto { return a + b; };
    })(fa)(fb);
    ASSERT_EQ(result.value(), 42);
}

// map2(f)(fa) is a reusable arrow F<B> → F<C>
TEST(Kernel_Ops_Map2, partial_application_is_reusable) {
    auto fa = pure<StructWithPure>(10);
    auto adder =
      map2([](int a) -> auto { return [a](int b) -> auto { return a + b; }; });
    auto fa_adder = adder(fa);
    ASSERT_EQ(fa_adder(pure<StructWithPure>(1)).value(), 11);
    ASSERT_EQ(fa_adder(pure<StructWithPure>(2)).value(), 12);
}

// type change — A, B, C all different
TEST(Kernel_Ops_Map2, combines_different_types) {
    auto fa = pure<StructWithPure>(42);
    auto fb = pure<StructWithPure>(String("hello"));
    auto result = map2([](int a) -> auto {
        return [a](const String& b) -> auto { return b + std::to_string(a); };
    })(fa)(fb);
    static_assert(std::same_as<decltype(result), StructWithPure<String>>);
    ASSERT_EQ(result.value(), "hello42");
}
