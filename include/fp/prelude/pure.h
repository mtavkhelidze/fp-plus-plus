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
using fp_cast = tools::cast::fp_cast<T>;

template <template <typename> class DataClass, typename T>
    requires fp::tools::apply::fp_has_apply<DataClass, T>
auto pure(T&& value) -> DataClass<fp_cast<T>> {
    using NT = fp_cast<T>;
    return DataClass<NT>::apply(std::forward<T>(value));
}
}  // namespace fp::prelude
#endif  // FP_PRELUDE_PURE_H
