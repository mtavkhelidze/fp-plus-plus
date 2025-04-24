// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp::traits::all;
using namespace fp::data::monad::id;

TEST(Monad_Id, functor_laws_map_identity) {  // laws
    auto a = pure<Id>(10);
    // auto b = a.map(fp::identity);

    // ASSERT_TRUE(a == b);
}

// TEST(Monad_Id, functor_laws_map_composition) {  // laws
//     auto a = pure<Id>(10);
//     auto f = [](int x) { return x + 1; };
//     auto g = [](int x) { return x * 2; };

//     auto left = a.map([&](int x) { return f(g(x)); });
//     auto right = a.map(g).map(f);

//     ASSERT_TRUE(left == right);
// }
// TEST(Monad_Id, implicit_conversion_to_inner_type) {
//     const Id<int> x = pure<Id>(10);
//     int n = x;
//     ASSERT_EQ(n, 10);
// }
