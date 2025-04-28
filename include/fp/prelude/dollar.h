#ifndef FP_PRELUDE_DOLLAR_H
#define FP_PRELUDE_DOLLAR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>

namespace fp::prelude {

/// Function application operator (similar to $ in Haskell). Equivalent to *
/// `f(a)`.
template <typename A, tools::arrow::Arrow<A> F>
inline constexpr auto dollar(F&& f, A&& a) noexcept -> decltype(auto) {
    return std::forward<F>(f)(std::forward<A>(a));
}
}  // namespace fp::prelude

#endif  // FP_PRELUDE_DOLLAR_H
