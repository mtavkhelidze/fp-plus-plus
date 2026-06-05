/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_INTERNAL_META_CAST_H
#define __FP_INTERNAL_META_CAST_H
#include <initializer_list>
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/types.h>
#include <fp/internal/storage/box.h>

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace fp::internal::meta::cast {

// NOLINTBEGIN(hicpp-avoid-c-arrays)
namespace {
    template <typename A>
    auto _deduce(A&& a) -> decltype(storage::Box(std::forward<A>(a)));
    // fallback via CTAD
    template <typename A>
    struct _cast {
        using type = typename decltype(_deduce(std::declval<A>()))::kind;
    };

    // char array → string
    template <typename U, std::size_t N>
        requires(std::same_as<std::decay_t<U>, char>)
    struct _cast<U[N]> {
        using type = data::String;
    };

    // non-char array → vector
    template <typename U, std::size_t N>
        requires(!std::same_as<std::decay_t<U>, char>)
    struct _cast<U[N]> {
        using type = data::Vector<std::decay_t<U>>;
    };

    template <typename U>
    struct _cast<std::initializer_list<U>> {
        using type = data::Vector<std::decay_t<U>>;
    };
}  // namespace

template <typename A>
using cast = typename _cast<A>::type;

// NOLINTEND(hicpp-avoid-c-arrays)
}  // namespace fp::internal::meta::cast

#endif  // __FP_INTERNAL_META_CAST_H
