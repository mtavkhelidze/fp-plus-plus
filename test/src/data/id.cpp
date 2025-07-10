// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/data/id.h>
#include <fp/traits/all.h>
#include <gtest/gtest.h>

using namespace fp::data::monad::id;
using namespace fp::traits::all;

TEST(Monad_Id, is_monad) {  //
    static_assert(Functor<Id<int>>);
    static_assert(Applicative<Id<int>>);
    static_assert(Monad<Id<int>>);
}
