#ifndef FP_PRELUDE_FLIP_H
#define FP_PRELUDE_FLIP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/tools/arrow.h>

namespace fp::prelude {

/**
 * Flips the first two arguments of a binary function.
 *
 * Given a function `f(a, b)`, `flip(f)(a, b)` returns `f(b, a)`.
 * Useful for reordering arguments in pipelines or point-free style.
 */
template <typename F>
constexpr auto flip(F&& f) {
    return [f = std::forward<F>(f)]<typename A, typename B>(
             A&& a, B&& b
           ) constexpr noexcept -> decltype(auto)
               requires tools::arrow::fp_is_binary_arrow<F, A, B>
    { return f(std::forward<B>(b), std::forward<A>(a)); };
}
}  // namespace fp::prelude
#endif  // FP_PRELUDE_FLIP_H
