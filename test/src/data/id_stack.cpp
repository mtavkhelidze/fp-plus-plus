// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/data/id.h>
#include <fp/prelude/pure.h>
#include <gtest/gtest.h>

using namespace fp::data::monad::id;
using namespace fp::prelude;

TEST(Monad_Id_Stack, construction) {
    auto id = pure<Id>(10);
    ASSERT_TRUE(id.is_stack());
    ASSERT_TRUE(id.has_value());
    ASSERT_EQ(id.value(), 10);
}
