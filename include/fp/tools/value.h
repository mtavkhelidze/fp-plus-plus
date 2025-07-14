#ifndef FP_TOOLS_APPLY_H
#define FP_TOOLS_APPLY_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/cast.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/rebind.h>

namespace fp::tools::value {

template <typename T>
using cast = fp::tools::cast::fp_cast<T>;

template <typename TC>
using inner_type = fp::tools::inner_type::fp_inner_type<TC>;

template <typename TC, typename A>
using rebind = fp::tools::rebind::fp_rebind<TC, A>;

template <typename TC>
concept HasValue = requires(TC t) {
    { t.value() } -> std::same_as<const cast<inner_type<TC>>&>;
};

template <typename TC>
concept HasApply = HasValue<TC> && requires(inner_type<TC> arg) {
    { TC::apply(arg) } -> std::same_as<rebind<TC, cast<inner_type<TC>>>>;
};

}  // namespace fp::tools::value
#endif  // FP_TOOLS_APPLY_H
