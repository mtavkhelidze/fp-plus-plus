#ifndef __FP_KERNEL_OPS_PRODUCT_H
#define __FP_KERNEL_OPS_PRODUCT_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/data.h>
#include <fp/kernel/ops/map2.h>

namespace fp::kernel::ops {

// product :: F<A> -> F<B> -> F<Tuple<A, B>>
constexpr auto product = kernel::ops::map2([]<typename A>(const A& a) -> auto {
    return [a]<typename B>(const B& b) -> data::Tuple<A, B> {
        return data::Tuple{a, b};
    };
});
}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_PRODUCT_H
