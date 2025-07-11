// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/core/all.h>
#include <fp/prelude/all.h>
#include <fp/traits/all.h>
#include <gtest/gtest.h>

using namespace fp::core;
using namespace fp::traits;
using namespace fp::prelude;

TEST(Core_Id, is_functor) {  //
    static_assert(IsFunctor<Id<int>>);
}

TEST(Core_Id, has_map) {  //
    static_assert(HasMap<Id<int>>);
}

TEST(Core_Id, instance_map_runtime) {
    auto id = pure<Id>(21);
    auto mapped = id.map(identity);
    EXPECT_EQ(mapped.value(), 21);
}

TEST(Core_Id_Functor, identity_law) {
    auto id = pure<Id>(42);
    auto mapped = id.map(identity);
    EXPECT_EQ(mapped.value(), id.value());
}

TEST(Core_Id_Functor, composition_law) {
    auto f = [](int x) { return x + 1; };
    auto g = [](int x) { return x * 2; };

    auto id = pure<Id>(10);
    auto mapped1 = id.map([&](int x) { return f(g(x)); });  // map(f ∘ g)
    auto mapped2 = id.map(g).map(f);                        // map(g).map(f)

    EXPECT_EQ(mapped1.value(), mapped2.value());
}

TEST(Core_Id_Functor, type_transformation) {
    auto id = pure<Id>(123);
    auto mapped = id.map([](int x) { return std::to_string(x); });
    EXPECT_EQ(mapped.value(), "123");
}

TEST(Core_Id_Functor, const_correctness) {
    auto id = pure<Id>(99);
    auto mapped = id.map([](int x) { return x * 3; });
    EXPECT_EQ(mapped.value(), 297);
}

TEST(Core_Id_Functor, exception_safety) {
    auto id = pure<Id>(7);
    bool threw = false;
    try {
        id.map([](int) -> int { throw std::runtime_error("fail"); });
    } catch (const std::runtime_error& e) {
        threw = true;
    }
    EXPECT_TRUE(threw);
    EXPECT_EQ(id.value(), 7);  // original remains intact
}
