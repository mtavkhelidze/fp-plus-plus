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

}  // namespace fp::traits
#endif // FP_TYPE_VALUE_VALUE_TRAITS_H
