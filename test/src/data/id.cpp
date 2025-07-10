// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/data/id.h>
#include <fp/prelude/pure.h>
#include <fp/tools/arrow.h>
#include <fp/tools/inner_type.h>
#include <fp/traits/functor.h>
#include <gtest/gtest.h>

using namespace fp::data::monad::id;
using namespace fp::traits::functor;
using namespace fp::prelude;
using namespace fp::tools::arrow;
using namespace fp::tools::inner_type;

template <Functor FA, typename F>
    requires Arrow<F, fp_inner_type<FA>>
static auto fmap(FA& fa, F& f) {
    return fa.map(f);
}

TEST(Monad_Id, is_functor) {  //
    static_assert(Functor<Id<int>>);
}

TEST(Monad_Id, fmap_identity) {
    Id<int> original = pure<Id>(42);
    auto result = fmap(original, identity);
    static_assert(std::same_as<decltype(result), Id<int>>);
    ASSERT_EQ(result.value(), 42);
}
