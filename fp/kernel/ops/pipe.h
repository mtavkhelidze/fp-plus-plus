/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_KERNEL_OPS_PIPE_H
#define __FP_KERNEL_OPS_PIPE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>

#include <utility>

namespace fp::kernel::ops {
// pipe :: (A -> B) -> (B -> C) -> A -> C
template <typename F, typename G>
constexpr auto pipe(F&& lhs, G&& rhs) -> decltype(auto) {
    return [lhs = std::forward<F>(lhs), rhs = std::forward<G>(rhs)]<typename A>(
             A&& a
           ) constexpr -> decltype(auto)
               requires(
                 internal::meta::arrow::is_arrow<F, A>
                 && internal::meta::arrow::is_arrow<
                   G, internal::meta::arrow::arrow_result<F, A>>
               )
    { return rhs(lhs(std::forward<A>(a))); };
}
// pipe :: (A -> B) -> (A -> B)
template <typename F>
constexpr auto pipe(F&& f) {
    return std::forward<F>(f);
}
// pipe :: (A -> B) -> (B -> C) -> ... -> (Y -> Z) -> A -> Z
template <typename F, typename G, typename... Rest>
constexpr auto pipe(F&& f, G&& g, Rest&&... rest) {
    return fp::kernel::ops::pipe(
      pipe(std::forward<F>(f), std::forward<G>(g)), std::forward<Rest>(rest)...
    );
}

}  // namespace fp::kernel::ops

#endif  // __FP_KERNEL_OPS_PIPE_H
