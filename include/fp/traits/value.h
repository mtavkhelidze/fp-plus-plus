#ifndef FP_TRAITS_VALUE_H
#define FP_TRAITS_VALUE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/tools/cast.h>
#include <fp/internal/tools/inner_type.h>
#include <fp/internal/tools/rebind.h>

#include <concepts>

namespace fp::traits::value {

template <typename TC>
concept HasValue = requires(TC t) {
    {
        t.value()
    } -> std::same_as<const fp::tools::cast::fp_cast<
      fp::tools::inner_type::fp_inner_type<TC>>&>;
};

template <typename TC>
concept HasApply =
  HasValue<TC> && requires(fp::tools::inner_type::fp_inner_type<TC> arg) {
      {
          TC::apply(arg)
      } -> std::same_as<fp::tools::rebind::fp_rebind<
        TC,
        fp::tools::cast::fp_cast<fp::tools::inner_type::fp_inner_type<TC>>>>;
  };

}  // namespace fp::traits::value
#endif  // FP_TRAITS_VALUE_H
