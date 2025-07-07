// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/data/id.h>
#include <fp/operators/all.h>
#include <fp/prelude/pure.h>
#include <fp/traits/eq.h>
#include <gtest/gtest.h>

using namespace fp::operators::all;
using namespace fp::prelude;
using namespace fp::traits::eq;

template <typename T>
using Id = fp::data::monad::id::Id<T>;

using namespace fp::prelude;

TEST(Monad_Id_Stack, construction) {
    // Proforma
    auto id = pure<Id>(10);
    ASSERT_TRUE(id.is_stack());
    ASSERT_TRUE(id.has_value());
    ASSERT_EQ(id.value(), 10);
}

TEST(Monad_Id_Stack, is_Eq) {
    static_assert(Eq<Id<int>>);
    auto a = pure<Id>(10);
    auto b = pure<Id>(10);
    ASSERT_TRUE(a == b);
}
//
// TEST(Monad_Id, functor_laws_map_composition) {  // laws
//     auto a = pure<Id>(10);
//     auto f = [](int x) { return x + 1; };
//     auto g = [](int x) { return x * 2; };
//
//     auto left = a.map([&](int x) { return f(g(x)); });
//     auto right = a.map(g).map(f);
//
//     ASSERT_TRUE(left == right);
// }
// TEST(Monad_Id, implicit_conversion_to_inner_type) {
//     const Id<int> x = pure<Id>(10);
//     int n = x;
//     ASSERT_EQ(n, 10);
// }
