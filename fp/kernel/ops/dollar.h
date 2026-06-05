/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_KERNAL_OPS_DOLLAR_H
#define __FP_KERNAL_OPS_DOLLAR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>

#include <utility>

namespace fp::kernel::ops {

// $ :: (A -> B) -> A -> B
// i.e. dollar(f, a) => f(a)
template <typename Fn, typename A>
    requires internal::meta::arrow::is_arrow<Fn, A>
constexpr auto dollar(Fn&& f, A&& a) -> decltype(auto) {
    return std::forward<Fn>(f)(std::forward<A>(a));
}

}  // namespace fp::kernel::ops
#endif  // __FP_KERNAL_OPS_DOLLAR_H
