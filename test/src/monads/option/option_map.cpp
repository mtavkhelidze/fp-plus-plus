#include <exception>
// keep for rapidcheck

#include <fp/fp.h>
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

#include "shorts.h"

using namespace fp;

auto identity = [](auto x) {
    decltype(x) y = x;
    static_assert(std::is_same_v<decltype(y), decltype(x)>);
    return y;
};

RC_GTEST_PROP(Option_Map, identity_law, (const int val)) {
    auto actual = Some(val).map(triple).equals(Some(val * 3));
    RC_ASSERT(actual);
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
