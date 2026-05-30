#ifndef __FP_KERNEL_OPS_AP_H
#define __FP_KERNEL_OPS_AP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/applicative.h>
#include <fp/internal/meta/meta.h>

#include <utility>

namespace fp::kernel::ops {
// ap :: F<A -> B> -> F<A> -> F<B>
template <typename FFn>
inline auto ap(FFn&& ff) -> auto {
    return
      [ff = std::forward<FFn>(ff)]<template <typename> typename F, typename A>(
        const F<A>& fa
      ) -> decltype(auto) { return core::Applicative<F>::ap(ff)(fa); };
};
}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_AP_H
