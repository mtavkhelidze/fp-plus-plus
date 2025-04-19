#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_PRELUDE_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_PRELUDE_H

#include <fp/tools.h>

#include <concepts>
#include <cstddef>
#include <utility>
#include <variant>

namespace fp::prelude {
struct __identity {
    template <typename A>
    constexpr auto operator()(A&& value) const noexcept -> A {
        return std::forward<A>(value);
    }
};

inline constexpr __identity identity{};
using identity_t = decltype(identity);
}  // namespace fp::prelude

namespace fp::prelude {
/**
 * Function application operator (similar to $ in Haskell). Equivalent to
 * `f(a)`.
 */
template <typename A>
constexpr auto dollar(std::invocable<A> auto f, A a) noexcept(noexcept(f(a)))
  -> decltype(f(a)) {
    return f(a);
}
}  // namespace fp::prelude
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
namespace fp::prelude {
/**
 * Pipe operator (similar to |> in Elm, used for chaining).
 * pipe(a, f) is equivalent to `f(a)`.
 */
template <typename A>
constexpr auto pipe(A a, auto&& f) noexcept(noexcept(f(a))) -> decltype(f(a)) {
    return f(a);
}
}  // namespace fp::prelude
namespace fp::prelude {
using namespace fp::tools::arrow;

/**
 * Flip function arguments: flip(f)(a, b) == f(b, a)
 */
template <typename F, typename A, typename B>
    requires fp_is_binary_arrow<F, A, B>
constexpr auto flip(F&& f) {
    return [f = std::forward<F>(f)](A&& a, B&& b) constexpr noexcept(
             noexcept(std::declval<F>()(std::declval<B>(), std::declval<A>()))
           ) -> fp_binary_arrow_result<F, B, A> {
        return f(std::forward<B>(b), std::forward<A>(a));
    };
}
}  // namespace fp::prelude

inline constexpr std::size_t __fp_align_16 = 16;
inline constexpr std::size_t __fp_align_32 = 32;

#define FP_PACKED [[gnu::packed]]
#define FP_ALIGN_PACKED_16 alignas(__fp_align_16) FP_PACKED
#define FP_ALIGN_PACKED_32 alignas(__fp_align_32) FP_PACKED

namespace fp::prelude {
using Nothing = std::monostate;  // is {}
}  // namespace fp::prelude

#endif  // FP_PRELUDE_H
