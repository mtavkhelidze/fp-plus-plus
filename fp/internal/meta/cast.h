#ifndef __FP_INTERNAL_META_CAST_H
#define __FP_INTERNAL_META_CAST_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/box.h>

#include <type_traits>

namespace fp::internal::meta::cast {

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
        using type = std::string;
    };

    // non-char array → vector
    template <typename U, std::size_t N>
        requires(!std::same_as<std::decay_t<U>, char>)
    struct _cast<U[N]> {
        using type = std::vector<std::decay_t<U>>;
    };
}  // namespace

template <typename A>
using cast = typename _cast<A>::type;
}  // namespace fp::internal::meta::cast

#endif  // __FP_INTERNAL_META_CAST_H
