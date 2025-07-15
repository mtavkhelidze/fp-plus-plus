#ifndef FP_PRELUDE_PURE_H
#define FP_PRELUDE_PURE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/cast.h>
#include <fp/traits/value.h>

namespace fp::prelude {

/**
 * Injects a value into the context of a type constructor `DataClass`.
 *
 * `pure<DataClass>(x)` wraps the value `x` into a `DataClass<T>` by calling
 * `DataClass<T>::apply(x)`, where `T` is the normalized form of the value type.
 *
 * This function is fundamental for Applicative and Monad abstractions.
 *
 * Example:
 *   auto idValue = pure<Id>(42); // Id<int> containing 42
 */
template <template <typename> typename DataClass, typename T>
    requires traits::value::HasApply<DataClass<tools::cast::fp_cast<T>>>
auto pure(T&& value) -> DataClass<tools::cast::fp_cast<T>> {
    using NT = tools::cast::fp_cast<T>;
    return DataClass<NT>::apply(std::forward<T>(value));
}
}  // namespace fp::prelude
#endif  // FP_PRELUDE_PURE_H
