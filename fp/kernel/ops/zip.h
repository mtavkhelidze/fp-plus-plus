#ifndef __FP_KERNEL_OPS_ZIP_H
#define __FP_KERNEL_OPS_ZIP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/ops/map2.h>
#include <fp/kernel/ops/product.h>

namespace fp::kernel::ops {

// zip :: F<A> -> F<B> -> F<Tuple<A, B>>
constexpr auto zip = product;

// zipWith :: (A -> B -> C) -> F<A> -> F<B> -> F<C>
template <typename Fn>
constexpr auto zipWith(Fn&& f) -> auto {
    return map2(std::forward<Fn>(f));
}
}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_ZIP_H
