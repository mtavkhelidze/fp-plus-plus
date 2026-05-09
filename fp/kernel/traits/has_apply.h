#ifndef __FP_KERNEL_TRAITS_HAS_APPLY_H
#define __FP_KERNEL_TRAITS_HAS_APPLY_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/traits/has_value.h>

#include <concepts>

namespace fp::kernel::traits::apply {

template <typename FA>
concept HasApply =
  value::HasValue<FA>
  && requires(internal::meta::inner_type::inner_type<FA> arg) {
         {
             FA::apply(arg)
         } -> std::same_as<fp::internal::meta::rebind::rebind<
           FA, fp::internal::meta::cast::cast<
                 fp::internal::meta::inner_type::inner_type<FA>>>>;
     };

}  // namespace fp::kernel::traits::apply
#endif  // __FP_KERNEL_TRAITS_HAS_APPLY_H
