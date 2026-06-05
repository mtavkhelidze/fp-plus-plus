/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_INTERNAL_META_REBIND_H
#define __FP_INTERNAL_META_REBIND_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/inner_type.h>

#include <type_traits>

namespace fp::internal::meta::rebind {

namespace {
    template <typename F>
    struct __rebind_instance {};

    template <template <typename> typename F, typename A>
    struct __rebind_instance<F<A>> {
        template <typename B>
        using type = F<std::decay_t<B>>;
    };

    template <template <typename, typename> typename F, typename A, typename B>
    struct __rebind_instance<F<A, B>> {
        template <typename C, typename D>
        using type = F<std::decay_t<C>, std::decay_t<D>>;
    };

    template <typename FA, typename FB>
    struct __is_same_f : std::false_type {};

    template <template <typename> typename F, typename A, typename B>
    struct __is_same_f<F<A>, F<B>> : std::true_type {};
}  // namespace

/// Transform F<A> into F<B>
template <typename F, typename B>
    requires(instance::is_unary_instance<F>)
using rebind = typename __rebind_instance<std::decay_t<F>>::template type<B>;

/// Transform F<A, B> into F<C, D>
template <typename F, typename C, typename D>
    requires(instance::is_binary_instance<F>)
using rebind_binary =
  typename __rebind_instance<std::decay_t<F>>::template type<C, D>;

template <typename FA, typename FB>
inline constexpr bool is_same_f =
  __is_same_f<std::decay_t<FA>, std::decay_t<FB>>::value;
}  // namespace fp::internal::meta::rebind

#endif  // __FP_INTERNAL_META_REBIND_H
