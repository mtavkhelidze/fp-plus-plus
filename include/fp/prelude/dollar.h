#ifndef FP_PRELUDE_DOLLAR_H
#define FP_PRELUDE_DOLLAR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/traits/traits.h>

namespace fp::prelude {

/**
 * Dollar operator: `f $ x`
 *
 * Function application with low precedence, allowing parentheses to be omitted.
 * Equivalent to Haskell's `$`; useful for chaining calls like `f $ g $ h(x)`
 * instead of `f(g(h(x)))`.
 *
 * Constraints:
 * - `F` must be an Arrow from `A`
 *
 * Example:
 *   auto result = dollar([](int x) { return x + 1; }, 41); // => 42
 */
template <typename A, traits::Arrow<A> F>
inline constexpr auto dollar(F&& f, A&& a) noexcept -> decltype(auto) {
    return std::forward<F>(f)(std::forward<A>(a));
}
}  // namespace fp::prelude

#endif  // FP_PRELUDE_DOLLAR_H
