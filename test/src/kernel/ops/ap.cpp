#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

#include <concepts>
#include <string>

using namespace fp;
using namespace fp::test;

// core behaviour — apply wrapped function to wrapped value
TEST(Kernel_Ops_Ap, applies_wrapped_function_to_wrapped_value) {
    auto ff = pure<StructWithPure>([](int x) -> int { return x * 2; });
    auto fa = pure<StructWithPure>(21);
    auto result = ap(ff)(fa);
    static_assert(std::same_as<decltype(result), StructWithPure<int>>);
    ASSERT_EQ(result.value(), 42);
}
// wrapped function is reusable — same ff, different fa
TEST(Kernel_Ops_Ap, wrapped_function_is_reusable) {
    auto f_double = pure<StructWithPure>([](int x) { return x * 2; });
    ASSERT_EQ(ap(f_double)(pure<StructWithPure>(10)).value(), 20);
    ASSERT_EQ(ap(f_double)(pure<StructWithPure>(21)).value(), 42);
}

// type change — wrapped function changes inner type
TEST(Kernel_Ops_Ap, changes_inner_type) {
    auto ff =
      pure<StructWithPure>([](int x) -> String { return std::to_string(x); });
    auto fa = pure<StructWithPure>(42);
    auto result = ap(ff)(fa);
    static_assert(std::same_as<decltype(result), StructWithPure<String>>);
    ASSERT_EQ(result.value(), "42");
}

// cast normalisation — function returns const char*, stored as String
TEST(Kernel_Ops_Ap, cstring_normalised_to_string) {
    auto ff = pure<StructWithPure>([](int) -> const char* { return "hello"; });
    auto fa = pure<StructWithPure>(42);
    auto result = ap(ff)(fa);
    static_assert(std::same_as<decltype(result), StructWithPure<String>>);
    ASSERT_EQ(result.value(), String("hello"));
}

// ap(validateAge)(validateName) — both must succeed
TEST(Kernel_Ops_Ap, combining_two_computations) {
    auto addAge = pure<StructWithPure>([](int age) -> auto {
        return [age](const String& name) -> String {
            return name + " age:" + std::to_string(age);
        };
    });
    auto fa = pure<StructWithPure>(42);
    auto step1 = ap(addAge)(fa);  // StructWithPure<String→String>
    auto fb = pure<StructWithPure>(String("Alice"));
    auto result = ap(step1)(fb);
    ASSERT_EQ(result.value(), "Alice age:42");
}
