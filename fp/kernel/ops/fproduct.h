/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_KERNEL_OPS_FPRODUCT_H
#define __FP_KERNEL_OPS_FPRODUCT_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/data.h>
#include <fp/kernel/ops/fmap.h>

#include <utility>

namespace fp::kernel::ops {

// @sig: fproduct :: Functor F => (A -> B) -> F<A> -> F<Tuple<A, B>>
template <typename Fn>
constexpr auto fproduct(Fn&& f) {
    return fmap([f = std::forward<Fn>(f)](auto&& a) -> decltype(auto) {
        return data::Tuple{a, f(a)};
    });
}

}  // namespace fp::kernel::ops

#endif  // __FP_KERNEL_OPS_FPRODUCT_H
