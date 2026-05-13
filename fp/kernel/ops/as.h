#ifndef __FP_KERNEL_OPS_AS_H
#define __FP_KERNEL_OPS_AS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/ops/always.h>
#include <fp/kernel/ops/fmap.h>
#include <fp/kernel/traits/traits.h>

#include <utility>

namespace fp::kernel::ops {
template <typename FA>
    requires kernel::traits::HasFunctor<FA>
auto as(const FA& fa) {
    return [fa]<typename B>(B&& b) -> decltype(auto) {
        return fmap(always(std::forward<B>(b)))(fa);
    };
}
}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_AS_H
