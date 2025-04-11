#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_SYNTAX_H
#define FP_SYNTAX_H

#include <concepts>

namespace fp::syntax {
/**
 * Function application operator (similar to $ in Haskell).
 * This operator applies the function `f` to the argument `a`.
 */
template <typename A>
constexpr auto operator&=(std::invocable<A> auto f, A a) -> decltype(f(a)) {
    return f(a);
}

/**
 * Function composition operator (similar to . in Haskell).
 * This operator composes two functions `lhs` and `rhs`, applying `rhs` first
 * and then `lhs`.
 */
template <typename F, typename G>
constexpr auto operator<<=(F&& lhs, G&& rhs) -> decltype(auto) {
    return [lhs = std::forward<F>(lhs),
            rhs = std::forward<G>(rhs)](auto a) -> decltype(lhs(rhs(a))) {
        return lhs(rhs(a));
    };
}

/**
 * Pipe operator (similar to |> in Elm, used for chaining).
 * This operator allows chaining computations, passing the result of one
 * computation to the next.
 */
template <typename A>
constexpr auto operator>=(A a, std::invocable<double> auto f)
  -> decltype(f(a)) {
    return f(a);
}

}  // namespace fp::syntax

#endif  // FP_SYNTAX_H
