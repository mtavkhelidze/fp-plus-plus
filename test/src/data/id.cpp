// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/data/id.h>
#include <fp/traits/functor.h>
#include <gtest/gtest.h>

using namespace fp::data::monad::id;
using namespace fp::traits::functor;
using namespace fp::prelude;
using namespace fp::tools::arrow;
using namespace fp::tools::inner_type;

TEST(Monad_Id, is_functor) {  //
    static_assert(Functor<Id<int>>);
}
