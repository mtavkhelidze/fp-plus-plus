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
