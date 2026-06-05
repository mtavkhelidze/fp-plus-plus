/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_INTERNAL_META_INNER_TYPE_H
#define __FP_INTERNAL_META_INNER_TYPE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/instance.h>

#include <concepts>
#include <type_traits>

namespace fp::internal::meta::inner_type {

namespace {
    template <typename F>
    struct _extract_inner_type {};

    template <template <typename> typename F, typename A>
    struct _extract_inner_type<F<A>> {
        using type = std::decay_t<A>;
    };
}  // namespace

/// If given F<A>, access A
template <typename F>
    requires instance::is_unary_instance<F>
using inner_type = typename _extract_inner_type<std::decay_t<F>>::type;

template <typename F, typename A>
    requires instance::is_unary_instance<F>
inline constexpr bool is_inner_type = std::same_as<inner_type<F>, A>;

template <typename FA, typename FB>
    requires(instance::is_unary_instance<FA> && instance::is_unary_instance<FB>)
inline constexpr bool is_same_inner_type =
  std::same_as<inner_type<std::decay_t<FA>>, inner_type<std::decay_t<FB>>>;

}  // namespace fp::internal::meta::inner_type

#endif  // __FP_INTERNAL_META_INNER_TYPE_H
