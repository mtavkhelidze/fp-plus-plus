/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_KERNEL_OPS_ZIP_H
#define __FP_KERNEL_OPS_ZIP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/ops/map2.h>
#include <fp/kernel/ops/product.h>

namespace fp::kernel::ops {

// @sig: zipWith :: Applicative F => (A -> B -> C) -> F<A> -> F<B> -> F<C>
// alias for map2
template <typename Fn>
constexpr auto zipWith(Fn&& f) -> auto {
    return map2(std::forward<Fn>(f));
}

// @sig: zip :: Applicative F => F<A> -> F<B> -> F<Tuple<A, B>>
// alias for product
constexpr auto zip = product;

}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_ZIP_H
