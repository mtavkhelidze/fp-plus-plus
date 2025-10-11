#ifndef FP_PRELUDE_PURE_H
#define FP_PRELUDE_PURE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/cast.h>
#include <fp/type/value/traits_value.h>

namespace fp::prelude {

/**
 * Lift a value into the context of a type constructor `F`.
 *
 * `pure<F>(x)` wraps the raw C++ value `x` (type `T`) into the FP-normalized
 * type `A` and then calls `F<A>::apply(x)`.
 *
 * Here:
 *   - `T` is the original C++ type of the value.
 *   - `A` is the FP-normalized type used inside the type constructor `F`.
 *
 * This corresponds to the `pure` method in Applicative/Monad abstractions.
 *
 * Example:
 *   auto idValue = pure<Id>(42); // Id<int> containing 42
 */
template <template <typename> typename F, typename T>
    requires traits::HasApply<F<tools::cast::fp_cast<T>>>
auto pure(T&& value) -> F<tools::cast::fp_cast<T>> {
    using A = tools::cast::fp_cast<T>;
    return F<A>::apply(std::forward<T>(value));
}
}  // namespace fp::prelude
#endif  // FP_PRELUDE_PURE_H
