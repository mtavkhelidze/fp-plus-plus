#ifndef FP_TOOLS_ARROW_H
#define FP_TOOLS_ARROW_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/inner_type.h>
#include <fp/tools/instance.h>

#include <functional>

namespace fp::tools::arrow {

template <typename F, typename A>
inline constexpr bool fp_is_arrow = requires(F f, A a) { std::invoke(f, a); }
                                 && !std::is_void_v<std::invoke_result_t<F, A>>;

template <typename F, typename A>
concept Arrow = fp_is_arrow<F, A>;

// 5. Extract the result type (optional helper)
template <typename F, typename A>
    requires Arrow<F, A>
using fp_arrow_result = std::decay_t<std::invoke_result_t<F, std::decay_t<A>>>;

template <typename F, typename A, typename B>
inline constexpr bool fp_is_binary_arrow = requires(F f, A a, B b) {
    std::invoke(f, a, b);
} && !std::is_void_v<std::invoke_result_t<F, A, B>>;

template <typename F, typename A, typename B>
concept BinaryArrow = fp_is_binary_arrow<F, A, B>;

template <typename F, typename A, typename B>
    requires BinaryArrow<F, A, B>
using fp_binary_arrow_result =
  std::decay_t<std::invoke_result_t<F, std::decay_t<A>, std::decay_t<B>>>;

template <typename F, typename A, typename B>
    requires BinaryArrow<F, A, B>
using fp_binary_arrow_result_v =
  std::decay_t<std::invoke_result<F, std::decay_t<A>, std::decay_t<B>>>;

}  // namespace fp::tools::arrow

namespace fp::tools::arrow {

using namespace instance;
using namespace inner_type;

template <typename F, typename A>
    requires Arrow<F, A>
inline constexpr bool fp_is_kleisli_arrow =
  fp_is_instance<fp_arrow_result<F, A>>;

template <typename F, typename A>
concept KleisliArrow = fp_is_kleisli_arrow<F, A>;

template <typename F, typename A>
    requires KleisliArrow<F, A>
using fp_kvalue = fp_arrow_result<F, A>;

template <typename F, typename A>
    requires KleisliArrow<F, A>
using fp_kvalue_type = fp_inner_type<fp_kvalue<F, A>>;

}  // namespace fp::tools::arrow

#endif  // FP_TOOLS_ARROW_H
