#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_OPERATORS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_OPERATORS_H

#include <concepts>
#include <utility>

namespace fp::prelude::identity {
struct __identity {
    template <typename A>
    constexpr A operator()(A&& value) const noexcept {
        return std::forward<A>(value);
    }
};

inline constexpr __identity identity{};
using identity_t = decltype(identity);
}  // namespace fp::prelude::identity

namespace fp::prelude::dollar {
/**
 * Function application operator (similar to $ in Haskell). Equivalent to
 * `f(a)`.
 */
template <typename A>
constexpr auto dollar(std::invocable<A> auto f, A a) noexcept(noexcept(f(a)))
  -> decltype(f(a)) {
    return f(a);
}
}  // namespace fp::prelude::dollar
namespace fp::prelude::dot {
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
}  // namespace fp::prelude::dot
namespace fp::prelude::pipe {
/**
 * Pipe operator (similar to |> in Elm, used for chaining).
 * pipe(a, f) is equivalent to `f(a)`.
 */
template <typename A>
constexpr auto pipe(A a, auto&& f) noexcept(noexcept(f(a))) -> decltype(f(a)) {
    return f(a);
}
}  // namespace fp::prelude::pipe

namespace fp::prelude::all {
using namespace fp::prelude::dollar;
using namespace fp::prelude::dot;
using namespace fp::prelude::identity;
using namespace fp::prelude::pipe;
}  // namespace fp::prelude::all

#endif  // FP_OPERATORS_H
