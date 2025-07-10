#ifndef FP_PRELUDE_PURE_H
#define FP_PRELUDE_PURE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/cast.h>
#include <fp/tools/value.h>

namespace fp::prelude {

template <typename T>
using cast = tools::cast::fp_cast<T>;

/// `pure`: Inject a value into the context of a type constructor `DataClass`.
///
/// Given a value `x` of type `T`, `pure<DataClass>(x)` wraps it into
/// `DataClass<T>` using `DataClass<T>::apply`.
///
/// This is the fundamental operation for Applicative functors and Monads.
///
/// Example:
/// ```cpp
/// auto idValue = pure<Id>(42); // Id<int> containing 42
/// ```
template <template <typename> typename DataClass, typename T>
    requires tools::value::HasApply<DataClass<cast<T>>>
auto pure(T&& value) -> DataClass<cast<T>> {
    using NT = cast<T>;
    return DataClass<NT>::apply(std::forward<T>(value));
}
}  // namespace fp::prelude
#endif  // FP_PRELUDE_PURE_H
