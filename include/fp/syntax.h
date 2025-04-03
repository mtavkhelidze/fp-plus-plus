#ifndef __FP_PP_SYNTAX_H__
#define __FP_PP_SYNTAX_H__

#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#include <functional>

namespace fp {
/**
 * Function application operator (similar to $ in Haskell).
 * This operator applies the function `f` to the argument `a`.
 */
template <typename A>
constexpr inline auto operator&=(std::invocable<A> auto f, A a)
  -> decltype(f(a)) {
    return f(a);
}

/**
 * Function composition operator (similar to . in Haskell).
 * This operator composes two functions `lhs` and `rhs`, applying `rhs` first
 * and then `lhs`.
 */
template <typename F, typename G>
constexpr inline auto operator<<=(F&& lhs, G&& rhs) -> decltype(auto) {
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
constexpr auto operator>=(A a, std::invocable<A> auto f) -> decltype(f(a)) {
    return f(a);
}

}  // namespace fp
#endif  // __FP_PP_SYNTAX_H__
