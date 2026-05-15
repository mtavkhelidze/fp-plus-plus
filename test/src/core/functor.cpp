#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <concepts>
#include <cstddef>
#include <string>

using namespace fp;
using namespace fp::test;

// lift morphisms into F
TEST(Core_Functor, map_lifts_morphism_A_to_B_into_FA_to_FB) {
    auto fa = pure<StructWithPure>(42);
    auto arrow = Functor<StructWithPure>::map([](int x) { return x + 1; });
    // arrow is F<A> → F<B> — a reusable first-class value
    auto result1 = arrow(fa);
    auto result2 = arrow(fa);
    static_assert(std::same_as<decltype(result1), StructWithPure<int>>);
    ASSERT_EQ(result1.value(), 43);
    // same arrow, same result — pure
    ASSERT_EQ(result2.value(), 43);
}

RC_GTEST_PROP(Core_Functor_Laws, identity_stack_storage, ()) {
    auto a = *rc::gen::arbitrary<int>();
    auto fa = pure<StructWithPure>(a);
    RC_ASSERT(fp::laws::FunctorLaws<StructWithPure>::identity(fa));
}

RC_GTEST_PROP(Core_Functor_Laws, identity_box_storage, ()) {
    auto a = *rc::gen::arbitrary<String>();
    auto fa = pure<StructWithPure>(a);
    RC_ASSERT(fp::laws::FunctorLaws<StructWithPure>::identity(fa));
}

RC_GTEST_PROP(Core_Functor_Laws, composition_stack_storage, ()) {
    auto a = *rc::gen::arbitrary<int>();
    auto fa = pure<StructWithPure>(a);
    auto f = [](int x) -> int { return x + 1; };
    auto g = [](int x) -> int { return x * 2; };
    RC_ASSERT(fp::laws::FunctorLaws<StructWithPure>::composition(fa, f, g));
}

RC_GTEST_PROP(Core_Functor_Laws, composition_box_storage, ()) {
    auto a = *rc::gen::arbitrary<String>();
    auto fa = pure<StructWithPure>(a);
    auto f = [](const String& x) -> String { return x + "1"; };
    auto g = [](const String& x) -> String { return x + "2"; };
    RC_ASSERT(fp::laws::FunctorLaws<StructWithPure>::composition(fa, f, g));
}

// composition with type change — A → B → C, not A → A → A
RC_GTEST_PROP(Core_Functor_Laws, composition_type_change, ()) {
    auto fa = pure<StructWithPure>(*rc::gen::arbitrary<int>());
    auto f = [](int x) -> String { return std::to_string(x); };
    auto g = [](const String& s) -> std::size_t { return s.size(); };
    RC_ASSERT(fp::laws::FunctorLaws<StructWithPure>::composition(fa, f, g));
}
