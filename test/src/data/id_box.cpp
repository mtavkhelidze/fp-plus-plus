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

TEST(Monad_Id_Box, construction) {
    // Proforma
    auto id = pure<Id>(std::string("hello"));
    ASSERT_TRUE(id.is_box());
    ASSERT_TRUE(id.has_value());
    ASSERT_EQ(id.value(), "hello");
}

TEST(Monad_Id_Box, is_Eq) {
    static_assert(Eq<Id<std::string>>);
    auto a = pure<Id>(std::string("hello"));
    auto b = pure<Id>(std::string("hello"));
    ASSERT_TRUE(a == b);
}

// TEST(Monad_Id, functor_laws_map_composition) {
//     auto a = pure<Id>(std::string("abc"));
//     auto f = [](const std::string& x) { return x + "!"; };
//     auto g = [](const std::string& x) { return x + "?"; };

//     auto left = a.map([&](const std::string& x) { return f(g(x)); });
//     auto right = a.map(g).map(f);

//     ASSERT_TRUE(left == right);
// }
TEST(Monad_Id_Box, implicit_conversion_to_inner_type) {
    const Id<std::string> x = pure<Id>(std::string("abc"));
    const auto n = x.value();
    ASSERT_EQ(n, "abc");
}
