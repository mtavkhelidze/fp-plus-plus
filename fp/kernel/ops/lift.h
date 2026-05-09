#ifndef FP_TYPE_VALUE_VALUE_PRE_LIFT_H
#define FP_TYPE_VALUE_VALUE_PRE_LIFT_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/ops/pure.h>

#include <utility>

namespace fp::kernel::ops {
/**
 * Lifts a function `f` into the context of`F`.
 *
 * Given a function `fn: A -> B`, `lift<F>(fn)` returns a function
 * `A -> F<B>` by composing `fn` with `pure<F>`.
 *
 * Example:
 *   auto lifted = lift<Id>([](int x) { return x + 1; });
 *   auto result = lifted(5); // result is Id<int> containing 6
 */
template <template <typename> typename F, typename Fn>
inline auto lift(Fn&& f) {
    return [f = std::forward<Fn>(f)](auto&& x) noexcept(
             noexcept(pure<F>(f(std::forward<decltype(x)>(x))))
           ) -> decltype(auto) {
        using B = decltype(x);
        static_assert(
          internal::meta::arrow::is_arrow<Fn, B>,
          "lift argument must be an arrow"
        );
        return pure<F>(f(std::forward<B>(x)));
    };
}
}  // namespace fp::kernel::ops

#endif  // FP_TYPE_VALUE_VALUE_PRE_LIFT_H
