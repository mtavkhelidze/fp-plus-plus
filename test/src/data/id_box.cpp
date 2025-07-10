// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/data/id.h>
#include <fp/operators/all.h>
#include <fp/prelude/pure.h>
#include <fp/traits/eq.h>
#include <gtest/gtest.h>

using namespace fp::data::monad::id;
using namespace fp::operators::all;
using namespace fp::prelude;
using namespace fp::prelude;
using namespace fp::traits::eq;

TEST(Monad_Id_Box, construction) {
    auto id = pure<Id>(std::string("hello"));
    ASSERT_TRUE(id.is_box());
    ASSERT_TRUE(id.has_value());
    ASSERT_EQ(id.value(), "hello");
}
