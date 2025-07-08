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

// TEST(Monad_Id_Stack, is_Eq) {
//     auto a = pure<Id>(10);
//     auto b = pure<Id>(10);
//     ASSERT_TRUE(a == b);
// }
