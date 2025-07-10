#ifndef FP_PRELUDE_DOLLAR_H
#define FP_PRELUDE_DOLLAR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>

namespace fp::prelude {

/// Dollar operator: `f $ x`
///
/// Function application with low precedence, allowing parentheses to be
/// omitted:
/// ```cpp
/// auto result = dollar(to_string, 42);  // equivalent to to_string(42)
/// ```
///
/// This is similar to Haskell's `$`, useful for writing:
/// ```cpp
/// auto result = f $ g $ h(x);
/// ```
/// instead of:
/// ```cpp
/// auto result = f(g(h(x)));
/// ```
///
/// Constraints:
/// - `F` must be an Arrow from `A`
///
/// Usage:
/// ```cpp
/// using namespace fp::prelude;
/// auto result = dollar([](int x) { return x + 1; }, 41); // => 42
/// ```
template <typename A, tools::arrow::Arrow<A> F>
inline constexpr auto dollar(F&& f, A&& a) noexcept -> decltype(auto) {
    return std::forward<F>(f)(std::forward<A>(a));
}
}  // namespace fp::prelude

#endif  // FP_PRELUDE_DOLLAR_H
