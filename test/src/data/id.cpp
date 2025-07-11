// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/data/all.h>
#include <fp/prelude/all.h>
#include <fp/traits/all.h>
#include <fp/types/all.h>
#include <gtest/gtest.h>

using namespace fp::data::all;
using namespace fp::traits::all;
using namespace fp::types;
using namespace fp::prelude;

TEST(Data_Id, is_functor) {  //
    static_assert(IsFunctor<Id<int>>);
}

TEST(Data_Id, has_map) {  //
    static_assert(HasMap<Id<int>>);
}

TEST(Data_Id, instance_map_runtime) {
    auto id = pure<Id>(21);
    auto mapped = id.map(identity);
    EXPECT_EQ(mapped.value(), 21);
}
