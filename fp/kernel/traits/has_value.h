#ifndef __FP_KERNEL_TRAITS_HAS_VALUE_H
#define __FP_KERNEL_TRAITS_HAS_VALUE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>

#include <concepts>

namespace fp::kernel::traits {

template <typename FA>
concept HasValue = requires(FA t) {
    {
        t.value()
    } -> std::same_as<const internal::meta::cast::cast<
      internal::meta::inner_type::inner_type<FA>>&>;
};
}  // namespace fp::kernel::traits
#endif  // __FP_KERNEL_TRAITS_HAS_VALUE_H
