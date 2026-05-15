#ifndef __TEST_INCLUDE_FP_TEST_H
#define __TEST_INCLUDE_FP_TEST_H
#pragma once

#include <fp/fp.h>

#include <string>

namespace fp::test {

template <typename A>
struct StructApply : fp::kernel::mixins::WithApply<StructApply<A>> {};

template <typename A>
struct StructFunctor
    : fp::kernel::mixins::WithApply<StructFunctor<A>>
    , fp::kernel::mixins::WithFunctor<StructFunctor<A>> {};
}  // namespace fp::test

namespace fp::test {

// int → String — format as price
constexpr auto formatPrice = [](const int& cents) -> String {
    return "$"
         + std::to_string(cents / 100)
         + "."
         + std::to_string(cents % 100);
};

// int → int — square the value
constexpr auto square = [](const int& x) -> int { return x * x; };

// curry: int → (String → Tuple<int, String>) — tag a string with an id
constexpr auto withId = [](const int& id) -> auto {
    return [&](const auto& s) -> Tuple<int, fp::cast<decltype(s)>> {
        return Tuple{id, s};
    };
};
}  // namespace fp::test
#endif  // __TEST_INCLUDE_FP_TEST_H
