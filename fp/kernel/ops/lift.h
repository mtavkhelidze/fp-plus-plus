#ifndef __FP_TYPE_VALUE_VALUE_PRE_LIFT_H
#define __FP_TYPE_VALUE_VALUE_PRE_LIFT_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/ops/pure.h>
#include <fp/kernel/traits/is_pure.h>

#include <utility>

namespace fp::kernel::ops {
/**
 * Lifts a function `f` into the context of`F`.
 *
 * Given a function `fn: A -> B`, `lift<F>(fn)` returns a function
 * `A -> F<B>` by composing `fn` with `pure<F>`.
 *
 * Example:
 *   aut    o lifted = lift<Id>([](int x) { return x + 1; });
 *   auto result = lifted(5); // result is Id<int> containing
 * Lift
 */
// lift :: WithPure F => (A -> B) -> A -> F<B>
template <template <typename> typename F, typename Fn>
    requires traits::IsWithPure<F>
inline auto lift(Fn&& ff) {
    return [ff = std::forward<Fn>(ff)]<typename A>(A&& a) -> decltype(auto)
               requires internal::meta::arrow::is_arrow<Fn, A>
    { return pure<F>(ff(std::forward<A>(a))); };
}
}  // namespace fp::kernel::ops

#endif  // __FP_TYPE_VALUE_VALUE_PRE_LIFT_H
