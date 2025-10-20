#include <fp/fp.h>
#include <gtest/gtest.h>

#include <string>

#include "eq_types.h"

using namespace fp;
using namespace fp::traits;

// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers

TEST(Eq_Traits, container_with_value_eq_is) { static_assert(IsEq<EqStruct>); }

TEST(Eq_Traits, container_with_value_eq_has) {
    static_assert(HasEquals<EqStruct<data::Whatever>>);
}

TEST(Eq_Traits, container_with_operators_eq_is) {
    static_assert(IsEqType<CustomWithOperators>);
}

TEST(Eq_Traits, container_with_operators_eq_has_not) {
    static_assert(!HasEquals<CustomWithOperators>);
}

TEST(Eq_Traits, container_without_value_eq_is) {
    static_assert(IsEq<CustomWithEq>);
}

TEST(Eq_Traits, container_without_value_eq_has) {
    static_assert(HasEquals<CustomWithEq<int>>);
}

TEST(Eq_Traits, ordinary_type_eq_is) {  //
    static_assert(IsEqType<std::string>);
}

TEST(Eq_Traits, ordinary_type_eq_has_not) {
    static_assert(!HasEquals<std::string>);
}

// NOLINTEND(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
