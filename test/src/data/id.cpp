// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/data/id.h>
#include <fp/operators/eq.h>
#include <fp/prelude/lift.h>
#include <fp/prelude/pure.h>
#include <fp/traits/all.h>
#include <gtest/gtest.h>

using namespace fp::data::monad::id;
using namespace fp::traits::all;
using namespace fp::prelude;
using namespace fp::operators::eq;

TEST(Monad_Id, is_monad) {  //
    static_assert(Functor<Id<int>>);
    static_assert(Applicative<Id<int>>);
    static_assert(Monad<Id<int>>);
}

TEST(Monad_Id, laws) {
    static_assert(Eq<Id<int>>);
    auto id = Id<int>::apply(42);

    auto f = [](int x) { return Id<std::string>::apply(std::to_string(x)); };
    auto g = [](const std::string& s) {
        return Id<std::size_t>::apply(s.size());
    };

    // Left identity: pure(x).flatMap(f) == f(x)
    EXPECT_TRUE(pure<Id>(42).flatMap(f).equals(f(42)));

    // Right identity: m.flatMap(pure) == m
    EXPECT_TRUE(id.flatMap(lift<Id>(identity)).equals(id));

    // Associativity: m.flatMap(f).flatMap(g) == m.flatMap(x => f(x).flatMap(g))
    auto lhs = id.flatMap(f).flatMap(g);
    auto rhs = id.flatMap([&](int x) { return f(x).flatMap(g); });
    // using eq operators
    EXPECT_TRUE(rhs == lhs);
}

TEST(Functor_Id, laws) {
    static_assert(Eq<Id<int>>);
    auto id = Id<int>::apply(42);

    // Functor identity: fmap id == id
    auto identity = [](int x) { return x; };
    EXPECT_TRUE(id.map(identity).equals(id));

    // Functor composition: fmap (f . g) == fmap f . fmap g
    auto f = [](int x) { return x + 1; };
    auto g = [](int x) { return x * 2; };
    auto composed = id.map([&](int x) { return f(g(x)); });
    auto mapped = id.map(g).map(f);
    EXPECT_TRUE(composed.equals(mapped));
}

// TEST(Applicative_Id, laws) {
//     // Applicative identity: pure id <*> v = v
//     auto v = Id<int>::apply(42);
//     auto pure_id = pure<Id>([](int x) { return x; });
//     auto applied_identity = v.ap(pure_id);
//     EXPECT_TRUE(applied_identity.equals(v));

//     // Applicative homomorphism: pure f <*> pure x = pure (f x)
//     auto f = [](int x) { return x + 1; };
//     auto x = 42;
//     auto lhs = pure<Id>(x).ap(pure<Id>(f));
//     auto rhs = pure<Id>(f(x));
//     EXPECT_TRUE(lhs.equals(rhs));

//     // Applicative interchange: u <*> pure y = pure ($ y) <*> u
//     auto u = pure<Id>([](int x) { return x + 2; });
//     auto y = 42;
//     auto lhs_interchange = pure<Id>(y).ap(u);
//     auto rhs_interchange = u.ap(pure<Id>([=](auto f) { return f(y); }));
//     EXPECT_TRUE(lhs_interchange.equals(rhs_interchange));
// }
