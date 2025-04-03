#include <exception>
// keep for rapidcheck

#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

#include <fp/fp>

#include "shorts.h"
using namespace fp;

RC_GTEST_PROP(Option_Map, identity_law, (const int val)) {
    auto actual = Some(val).map(id);
    auto expected = Some(val);
    RC_ASSERT(actual.equals(expected));
}

RC_GTEST_PROP(Option_Map, composition_law, (const int val)) {
    auto actual = Some(val).map(triple).map(increment);
    auto expected = Some(val).map(increment <<= triple);
    RC_ASSERT(actual.equals(expected));
}

RC_GTEST_PROP(Option_Map, homomorphism_law, (const int val)) {
    auto actual = Some(val).map(increment);
    auto expected = Some(increment &= val);
    RC_ASSERT(actual.equals(expected));
}

RC_GTEST_PROP(Option_Map, identity_law_none, ()) {
    auto actual = None<int>().map(id);
    auto expected = None<int>();
    RC_ASSERT(actual.equals(expected));
}

RC_GTEST_PROP(Option_Map, composition_law_none, ()) {
    auto actual = None<int>().map(triple).map(increment);
    auto expected = None<int>().map(increment <<= triple);
    RC_ASSERT(actual.equals(expected));
}

RC_GTEST_PROP(Option_Map, homomorphism_law_none, ()) {
    auto actual = None<int>().map(increment);
    auto expected = None<int>();
    RC_ASSERT(actual.equals(expected));
}
