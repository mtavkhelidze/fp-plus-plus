#ifndef FP_TOOLS_APPLY_H
#define FP_TOOLS_APPLY_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/cast.h>
#include <fp/tools/inner_type.h>

#include <utility>

namespace fp::tools::value {

template <typename TC>
using inner_type = fp::tools::inner_type::fp_inner_type<TC>;

template <typename T>
concept HasValue = requires(T t) {
    { t.value() };
};

template <typename T>
concept HasApply =
  requires(tools::inner_type::fp_inner_type<T> arg) { T::apply(arg); };

}  // namespace fp::tools::value
#endif  // FP_TOOLS_APPLY_H
