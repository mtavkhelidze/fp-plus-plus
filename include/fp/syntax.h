#ifndef __FP_PP_SYNTAX_H__
#define __FP_PP_SYNTAX_H__

#ifndef __FP_PLUS_PLUS__
#error "This file must be included from fp/fp"
#endif

#include <concepts>
#include <functional>

namespace fp {

/**
 * Function application operator (similar to $ in Haskell).
 * This operator applies the function `f` to the argument `a`.
 */
template <typename A>
constexpr auto operator&=(std::invocable<A> auto f, A a) {
    return f(a);
}

/**
 * Function composition operator (similar to . in Haskell).
 * This operator composes two functions `lhs` and `rhs`, applying `rhs` first
 * and then `lhs`.
 */
template <typename F, typename G>
    requires std::invocable<F, typename std::invoke_result_t<G>::type>
auto operator<<(F&& lhs, G&& rhs) {
    return [lhs = std::forward<F>(lhs), rhs = std::forward<G>(rhs)](auto a) {
        return lhs(rhs(a));  // Apply rhs first, then lhs
    };
}

/**
 * Pipe operator (similar to >>= in Haskell, used for chaining).
 * This operator allows chaining computations, passing the result of one
 * computation to the next.
 */
template <typename A>
constexpr auto operator>>=(A a, std::invocable<A> auto f) {
    return f(a);
}

}  // namespace fp
#endif  // __FP_PP_SYNTAX_H__
