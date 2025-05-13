#ifndef FP_PRELUDE_PURE_H
#define FP_PRELUDE_PURE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/apply.h>
#include <fp/tools/cast.h>

namespace fp::prelude {

template <typename T>
using cast = tools::cast::fp_cast<T>;

template <template <typename> class TC, typename T>
concept HasApply = tools::storage::fp_has_apply<TC, T>;

template <template <typename> typename DataClass, typename T>
    requires HasApply<DataClass, T>
auto pure(T&& value) -> DataClass<cast<T>> {
    using NT = cast<T>;
    return DataClass<NT>::apply(std::forward<T>(value));
}
}  // namespace fp::prelude
#endif  // FP_PRELUDE_PURE_H
