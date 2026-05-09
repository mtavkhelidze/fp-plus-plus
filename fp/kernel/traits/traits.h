#ifndef __FP_KERNEL_TRAITS_TRAITS_H
#define __FP_KERNEL_TRAITS_TRAITS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/traits/has_apply.h>
#include <fp/kernel/traits/has_value.h>

namespace fp::kernel::traits {
using fp::kernel::traits::apply::HasApply;
using fp::kernel::traits::value::HasValue;
}  // namespace fp::kernel::traits

#endif  // __FP_KERNEL_TRAITS_TRAITS_H
