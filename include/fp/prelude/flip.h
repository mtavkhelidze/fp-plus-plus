#ifndef FP_PRELUDE_FLIP_H
#define FP_PRELUDE_FLIP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>

namespace fp::prelude {

/**
 * Flip function arguments: flip(f)(a, b) == f(b, a)
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
