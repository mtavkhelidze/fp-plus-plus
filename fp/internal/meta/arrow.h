/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_INTERNAL_META_ARROW_H
#define __FP_INTERNAL_META_ARROW_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/cast.h>
#include <fp/internal/meta/inner_type.h>
#include <fp/internal/meta/instance.h>

#include <concepts>
#include <type_traits>

namespace fp::internal::meta::arrow {

// Fn :: A -> B
template <typename Fn, typename A>
concept is_arrow = std::invocable<std::decay_t<Fn>, cast::cast<A>>
                && !std::is_void_v<std::invoke_result_t<Fn, cast::cast<A>>>;

// Result of Fn :: A -> B
template <typename Fn, typename A>
    requires is_arrow<Fn, A>
using arrow_result = std::invoke_result_t<std::decay_t<Fn>, cast::cast<A>>;

// Fn :: A -> B -> C
template <typename Fn, typename A, typename B>
concept is_sparrow = is_arrow<Fn, A> && is_arrow<arrow_result<Fn, A>, B>;

}  // namespace fp::internal::meta::arrow

#endif  // __FP_INTERNAL_META_ARROW_H
