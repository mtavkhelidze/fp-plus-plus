#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_OPERATORS_H
#define FP_OPERATORS_H

#include <concepts>

namespace fp::operators {
/**
 * Function application operator (similar to $ in Haskell). Equivalent to
 * `f(a)`.
 */
template <typename A>
constexpr auto dollar(std::invocable<A> auto f, A a) noexcept(noexcept(f(a)))
  -> decltype(f(a)) {
    return f(a);
}

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

/**
 * Pipe operator (similar to |> in Elm, used for chaining).
 * pipe(a, f) is equivalent to `f(a)`.
 */
template <typename A>
constexpr auto pipe(A a, auto&& f) noexcept(noexcept(f(a))) -> decltype(f(a)) {
    return f(a);
}

}  // namespace fp::operators

#endif  // FP_OPERATORS_H
