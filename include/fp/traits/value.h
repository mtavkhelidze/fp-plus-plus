#ifndef FP_TRAITS_VALUE_H
#define FP_TRAITS_VALUE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/inner_type.h>
namespace fp::traits::value {

template <typename T>
concept HasValue = requires(T t) {
    { t.value() };
};

template <typename T>
concept HasApply =
  requires(tools::inner_type::fp_inner_type<T> arg) { T::apply(arg); };

}  // namespace fp::traits::value

#endif  // FP_TRAITS_VALUE_H
