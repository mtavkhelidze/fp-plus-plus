#ifndef __FP_KERNEL_MIXINS_MIXINS_H
#define __FP_KERNEL_MIXINS_MIXINS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/mixins/with_value.h>

namespace fp::kernel::mixins {
using namespace fp::kernel::mixins::value;
}  // namespace fp::kernel::mixins

#endif  // __FP_KERNEL_MIXINS_MIXINS_H
