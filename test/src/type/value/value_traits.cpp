#include <fp/fp.h>
#include <gtest/gtest.h>

#include "value_types.h"

using namespace fp;
using namespace fp::traits;

TEST(Value_Traits, has_value) {
    static_assert(HasValue<ValueStruct<data::Whatever>>);
}

TEST(Value_Traits, has_apply) {  //
    static_assert(HasApply<ValueStruct<int>>);
}
