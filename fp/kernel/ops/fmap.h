#ifndef __FP_KERNEL_OPS_FMAP_H
#define __FP_KERNEL_OPS_FMAP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/core.h>
#include <fp/internal/meta/meta.h>

#include <utility>

namespace fp::kernel::ops {
// fmap :: WithPure F => (A -> B) -> F<A>-> F<B>
constexpr auto fmap = []<typename Fn>(Fn&& f) -> auto {
    return
      [f = std::forward<Fn>(f)]<template <typename> typename F, typename A>(
        const F<A>& fa
      ) -> decltype(auto)
          requires(internal::meta::arrow::is_arrow<Fn, A>)
    { return fp::core::Functor<F>::map(f)(fa); };
};

}  // namespace fp::kernel::ops

#endif  // __FP_KERNEL_OPS_FMAP_H
