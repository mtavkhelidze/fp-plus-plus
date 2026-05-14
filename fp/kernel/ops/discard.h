#ifndef __FP_KERNEL_OPS_DISCARD_H
#define __FP_KERNEL_OPS_DISCARD_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/data.h>
#include <fp/kernel/ops/as.h>

namespace fp::kernel::ops {

inline auto discard = as(data::nothing);

}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_DISCARD_H
