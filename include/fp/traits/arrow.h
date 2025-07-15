#ifndef FP_TRAITS_ARROW_H
#define FP_TRAITS_ARROW_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>

namespace fp::traits::arrow {
template <typename F, typename A>
concept Arrow = tools::arrow::fp_is_arrow<F, A>;

template <typename F, typename A, typename B>
concept BinaryArrow = tools::arrow::fp_is_binary_arrow<F, A, B>;

template <typename F, typename A>
concept KleisliArrow = tools::arrow::fp_is_kleisli_arrow<F, A>;

}  // namespace fp::traits::arrow
#endif  // FP_TRAITS_ARROW_H
