#ifndef FP_TRAITS_ARROW_H
#define FP_TRAITS_ARROW_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>

namespace fp::traits {
template <typename Fn, typename A, typename B>
concept Arrow = requires(Fn f, A a) {
    { f(a) } -> std::convertible_to<B>;
};

template <typename Fn, typename A>
concept IsArrow = tools::arrow::fp_is_arrow<Fn, A>;

template <typename Fn, typename A, typename B>
concept IsBinaryArrow = tools::arrow::fp_is_binary_arrow<Fn, A, B>;

template <typename Fn, typename A>
concept IsKleisliArrow = tools::arrow::fp_is_kleisli_arrow<Fn, A>;

}  // namespace fp::traits
#endif  // FP_TRAITS_ARROW_H
