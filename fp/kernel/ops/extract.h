#ifndef __FP_KERNEL_OPS_EXTRACT_H
#define __FP_KERNEL_OPS_EXTRACT_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/traits/traits.h>

namespace fp::kernel::ops {

inline constexpr auto extract = []<typename FA>(const FA& fa) -> decltype(auto)
    requires traits::HasApply<FA>
{ return fa.value(); };

}  // namespace fp::kernel::ops

#endif  // __FP_KERNEL_OPS_EXTRACT_H
