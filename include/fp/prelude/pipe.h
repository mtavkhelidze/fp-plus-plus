#ifndef FP_PRELUDE_PIPE_H
#define FP_PRELUDE_PIPE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

namespace fp::prelude {
/// Pipe operator (similar to `|>` in Elm, used for chaining).
/// `pipe(a, f)` is equivalent to `f(a)`.
template <typename A>
constexpr auto pipe(A a, auto&& f) -> decltype(auto) {
    return f(a);
}
}  // namespace fp::prelude

#endif  // FP_PRELUDE_PIPE_H
