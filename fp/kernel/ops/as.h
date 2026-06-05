/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

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

// as :: Functor F => A -> F<B> -> F<A>
template <typename A>
inline auto as(A&& a) -> decltype(auto) {
    return fmap(always(std::forward<A>(a)));
};

}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_AS_H
