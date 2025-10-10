#ifndef FP_OPERATORS_SEMIGROUP_H
#define FP_OPERATORS_SEMIGROUP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/traits/traits.h>

#include <utility>

namespace fp::operators::semigroup {

template <traits::semigroup::Semigroup M>
constexpr auto operator+(M&& lhs, M&& rhs) {
    return combine(std::forward<M>(lhs), std::forward<M>(rhs));
}

template <traits::semigroup::Semigroup M>
constexpr auto operator+(const M& lhs, const M& rhs) {
    return combine(lhs, rhs);
}
}  // namespace fp::operators::semigroup

#endif  // FP_OPERATORS_SEMIGROUP_H
