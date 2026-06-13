/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_KERNEL_OPS_MAP2_H
#define __FP_KERNEL_OPS_MAP2_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/ops/ap.h>
#include <fp/kernel/ops/fmap.h>
#include <fp/kernel/traits/is_applicative.h>

namespace fp::kernel::ops {

// @sig: map2 :: Applicative F => (A -> B -> C) -> F<A> -> F<B> -> F<C>
template <typename Fn>
constexpr auto map2(Fn&& f) -> auto {
    return
      [f = std::forward<Fn>(f)]<template <typename> typename F, typename A>(
        const F<A>& fa
      ) -> auto
          requires(
            kernel::traits::IsApplicative<F>
            && internal::meta::arrow::is_arrow<Fn, A>
          )
    { return fp::kernel::ops::ap(fp::kernel::ops::fmap(f)(fa)); };
}

}  // namespace fp::kernel::ops

#endif  // __FP_KERNEL_OPS_MAP2_H
