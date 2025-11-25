#ifndef FP_TOOLS_ARROW_H
#define FP_TOOLS_ARROW_H
#include <ratio>
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/inner_type.h>
#include <fp/tools/instance.h>

#include <concepts>
#include <type_traits>

namespace fp::tools::arrow {

template <typename Fn, typename A>
inline constexpr bool fp_is_arrow =
  std::invocable<std::decay_t<Fn>, A>
  && !std::is_void_v<std::invoke_result_t<Fn, A>>;

template <typename Fn, typename A>
    requires fp_is_arrow<Fn, A>
using fp_arrow_result = std::decay_t<std::invoke_result_t<Fn, std::decay_t<A>>>;

template <typename Fn, typename A, typename B>
inline constexpr bool fp_is_binary_arrow = requires(Fn f, A a, B b) {
    std::invoke(f, a, b);
} && !std::is_void_v<std::invoke_result_t<Fn, A, B>>;

template <typename Fn, typename A, typename B>
    requires fp_is_binary_arrow<Fn, A, B>
using fp_binary_arrow_result =
  std::decay_t<std::invoke_result_t<Fn, std::decay_t<A>, std::decay_t<B>>>;

template <typename Fn, typename A, typename B>
    requires fp_is_binary_arrow<Fn, A, B>
using fp_binary_arrow_result_v =
  std::decay_t<std::invoke_result<Fn, std::decay_t<A>, std::decay_t<B>>>;

}  // namespace fp::tools::arrow

namespace fp::tools::arrow {

template <typename F, typename A>
    requires fp_is_arrow<F, A>
inline constexpr bool fp_is_kleisli_arrow =
  instance::fp_is_instance<fp_arrow_result<F, A>>;

template <typename F, typename A>
    requires fp_is_kleisli_arrow<F, A>
using fp_kleisli_arrow_result = fp_arrow_result<F, A>;

template <typename F, typename A>
    requires fp_is_kleisli_arrow<F, A>
using fp_kleisli_arrow_result_value_type =
  inner_type::fp_inner_type<fp_kleisli_arrow_result<F, A>>;

}  // namespace fp::tools::arrow

#endif  // FP_TOOLS_ARROW_H
