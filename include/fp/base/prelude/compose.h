#ifndef FP_BASE_PRELUDE_COMPOSE_H
#define FP_BASE_PRELUDE_COMPOSE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/base/traits.h>
#include <fp/tools/all.h>

namespace fp::prelude {

/// Compose two functions: `compose(f, g)(x)` is `f(g(x))`
/// Constraints
/// - `g` must be an Arrow from A
/// - `f` must be an Arrow from `g(A)`
///
/// This is equivalent to the Haskell `(.)` operator.
/// Also known as `f ∘ g`, or `andThen` in some languages.
template <typename F, typename G>
constexpr auto compose(F&& lhs, G&& rhs) noexcept {
    return [lhs = std::forward<F>(lhs), rhs = std::forward<G>(rhs)]<typename A>(
             A&& a
           ) constexpr noexcept -> decltype(auto)
               requires(
                 traits::Arrow<G, A>
                 && traits::Arrow<F, tools::arrow::fp_arrow_result<G, A>>
               )
    { return lhs(rhs(std::forward<A>(a))); };
}
}  // namespace fp::prelude
#endif  // FP_BASE_PRELUDE_COMPOSE_H
