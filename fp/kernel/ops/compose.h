/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_KERNEL_OPS_COMPOSE_H
#define __FP_KERNEL_OPS_COMPOSE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>

#include <utility>

namespace fp::kernel::ops {
// compose :: (B -> C) -> (A -> B) -> A -> C
template <typename F, typename G>
constexpr auto compose(F&& lhs, G&& rhs) -> decltype(auto) {
    return [lhs = std::forward<F>(lhs), rhs = std::forward<G>(rhs)]<typename A>(
             A&& a
           ) constexpr -> decltype(auto)
               requires(
                 internal::meta::arrow::is_arrow<G, A>
                 && internal::meta::arrow::is_arrow<
                   F, internal::meta::arrow::arrow_result<G, A>>
               )
    { return lhs(rhs(std::forward<A>(a))); };
}

// compose :: (A -> B) -> (A -> B)
template <typename F>
constexpr auto compose(F&& f) {
    return std::forward<F>(f);
}

// compose :: (C -> D) -> (B -> C) -> ... -> (A -> B) -> A -> D
template <typename F, typename G, typename... Rest>
constexpr auto compose(F&& f, G&& g, Rest&&... rest) {
    return fp::kernel::ops::compose(
      std::forward<F>(f),
      compose(std::forward<G>(g), std::forward<Rest>(rest)...)
    );
}

}  // namespace fp::kernel::ops

#endif  // __FP_KERNEL_OPS_COMPOSE_H
