#ifndef FP_TYPE_VALUE_VALUE_TRAITS_H
#define FP_TYPE_VALUE_VALUE_TRAITS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/cast.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/rebind.h>

#include <concepts>

namespace fp::traits {

template <typename FA>
concept HasValue = requires(FA t) {
    {
        t.value()
    } -> std::same_as<const fp::tools::cast::fp_cast<
      fp::tools::inner_type::fp_inner_type<FA>>&>;
};

template <typename FA>
concept HasApply =
  HasValue<FA> && requires(fp::tools::inner_type::fp_inner_type<FA> arg) {
      {
          FA::apply(arg)
      } -> std::same_as<fp::tools::rebind::fp_rebind<
        FA,
        fp::tools::cast::fp_cast<fp::tools::inner_type::fp_inner_type<FA>>>>;
  };

}  // namespace fp::traits
#endif  // FP_TYPE_VALUE_VALUE_TRAITS_H
