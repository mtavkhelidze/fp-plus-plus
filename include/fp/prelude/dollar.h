#ifndef FP_PRELUDE_DOLLAR_H
#define FP_PRELUDE_DOLLAR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <concepts>

namespace fp::prelude {

/// Function application operator (similar to $ in Haskell). Equivalent to *
/// `f(a)`.
template <typename A>
inline constexpr auto dollar(std::invocable<A> auto f, A a) noexcept(
  noexcept(f(a))
) -> decltype(f(a)) {
    return f(a);
}
}  // namespace fp::prelude

#endif  // FP_PRELUDE_DOLLAR_H
