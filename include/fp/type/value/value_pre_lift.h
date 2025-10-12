#ifndef FP_PRELUDE_LIFT_H
#define FP_PRELUDE_LIFT_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/type/value/value_pre_pure.h>

#include <utility>

namespace fp::prelude {
/**
 * Lifts a function `f` into the context of a type constructor `TC`.
 *
 * Given a function `f: A -> B`, `lift<TC>(f)` returns a function
 * `A -> TC<B>` by composing `f` with `pure<TC>`.
 *
 * Useful for working with applicative functors or monads.
 *
 * Example:
 *   auto lifted = lift<Id>([](int x) { return x + 1; });
 *   auto result = lifted(5); // result is Id<int> containing 6
 */
template <template <typename> typename TC, typename F>
constexpr auto lift(F&& f) {
    return
      [f = std::forward<F>(f)](auto&& x) constexpr noexcept(
        noexcept(pure<TC>(f(std::forward<decltype(x)>(x))))
      ) -> decltype(auto) { return pure<TC>(f(std::forward<decltype(x)>(x))); };
};
}  // namespace fp::prelude
#endif  // FP_PRELUDE_LIFT_H
