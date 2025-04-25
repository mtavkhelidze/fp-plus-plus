#ifndef FP_PRELUDE_DOT_H
#define FP_PRELUDE_DOT_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <utility>

namespace fp::prelude {
/**
 * Function composition operator (similar to . in Haskell). dot(f, g) is
 * equivalent to f(g(x)).
 */
template <typename F, typename G>
constexpr auto dot(F&& lhs, G&& rhs) noexcept(
  noexcept(lhs(rhs(std::declval<int>())))
) -> decltype(auto) {
    return [lhs = std::forward<F>(lhs), rhs = std::forward<G>(rhs)](
             auto a
           ) constexpr noexcept(noexcept(lhs(rhs(a)))
           ) -> decltype(lhs(rhs(a))) { return lhs(rhs(a)); };
}
}  // namespace fp::prelude
#endif  // FP_PRELUDE_DOT_H
