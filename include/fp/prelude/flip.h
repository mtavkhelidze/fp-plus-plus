#ifndef FP_PRELUDE_FLIP_H
#define FP_PRELUDE_FLIP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools.h>

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
#endif  // FP_PRELUDE_FLIP_H
