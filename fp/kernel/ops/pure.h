#ifndef __FP_TYPE_VALUE_VALUE_PRE_PURE_H
#define __FP_TYPE_VALUE_VALUE_PRE_PURE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/traits/is_pure.h>

namespace fp::kernel::ops {

/**
 * Lift a value into the context of a type constructor `F`.
 *
 * `pure<F>(x)` wraps the raw C++ value `x` (type `T`) into the
 * FP-normalized (fp::cast-ed) type `A` and then calls `F<A>::pure(x)`.
 *
 * Here:
 *   - `T` is the original C++ type of the value.
 *   - `A` is the FP-normalized type used inside the type constructor `F`.
 *
 * Example:
 *   auto idValue = pure<Id>(42); // Id<int> containing 42
 */
// pure :: WithPure F, A = fp::cast<T> => T -> F<A>
template <template <typename> typename F, typename T>
    requires traits::HasPure<F<internal::meta::cast::cast<T>>>
inline auto pure(T&& value) -> F<internal::meta::cast::cast<T>> {
    return F<internal::meta::cast::cast<T>>::pure(std::forward<T>(value));
}
}  // namespace fp::kernel::ops

#endif  // __FP_TYPE_VALUE_VALUE_PRE_PURE_H
