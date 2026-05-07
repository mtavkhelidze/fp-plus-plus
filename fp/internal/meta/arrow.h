#ifndef __FP_INTERNAL_META_ARROW_H
#define __FP_INTERNAL_META_ARROW_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/inner_type.h>
#include <fp/internal/meta/instance.h>

#include <concepts>
#include <type_traits>

namespace fp::internal::meta::arrow {

template <typename Fn, typename A>
constexpr bool is_arrow = std::invocable<std::decay_t<Fn>, A>
                       && !std::is_void_v<std::invoke_result_t<Fn, A>>;

template <typename Fn, typename A>
    requires is_arrow<Fn, A>
using arrow_result = std::decay_t<std::invoke_result_t<Fn, std::decay_t<A>>>;

template <typename Fn, typename A, typename B>
constexpr bool is_binary_arrow = requires(Fn f, A a, B b) {
    std::invoke(f, a, b);
} && !std::is_void_v<std::invoke_result_t<Fn, A, B>>;

template <typename Fn, typename A, typename B>
    requires is_binary_arrow<Fn, A, B>
using binary_arrow_result =
  std::decay_t<std::invoke_result_t<Fn, std::decay_t<A>, std::decay_t<B>>>;

template <typename Fn, typename A, typename B>
    requires is_binary_arrow<Fn, A, B>
using binary_arrow_result_v =
  std::decay_t<std::invoke_result<Fn, std::decay_t<A>, std::decay_t<B>>>;

}  // namespace fp::internal::meta::arrow

#endif  // __FP_INTERNAL_META_ARROW_H
