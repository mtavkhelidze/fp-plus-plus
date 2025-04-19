#ifndef FP_TRAITS_SEMIGROUP_H
#define FP_TRAITS_SEMIGROUP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <concepts>

namespace fp::traits::semigroup {
/**
 * @brief A Semigroup provides an associative binary operation via `combine(a,
 * b)`.
 *
 * The `combine` function must be found via ADL and satisfy the associativity
 * law: combine(a, combine(b, c)) == combine(combine(a, b), c)
 */
template <typename S>
concept Semigroup = requires(S a, S b) {
    { combine(a, b) } -> std::same_as<S>;
};

}  // namespace fp::traits::semigroup

#endif  // FP_TRAITS_SEMIGROUP_H
