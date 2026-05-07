#ifndef __FP_INTERNAL_META_KLEISLI_H
#define __FP_INTERNAL_META_KLEISLI_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/arrow.h>
#include <fp/internal/meta/inner_type.h>
#include <fp/internal/meta/instance.h>

namespace fp::internal::meta::kleisli {

template <typename F, typename A>
    requires arrow::is_arrow<F, A>
inline constexpr bool is_kleisli_arrow =
  instance::is_instance<arrow::arrow_result<F, A>>;

template <typename F, typename A>
    requires is_kleisli_arrow<F, A>
using fp_kleisli_arrow_result = arrow::arrow_result<F, A>;

template <typename F, typename A>
    requires is_kleisli_arrow<F, A>
using fp_kleisli_arrow_result_value_type =
  inner_type::inner_type<fp_kleisli_arrow_result<F, A>>;

template <typename F, typename A, typename B>
concept Kleisli = is_kleisli_arrow<F, A>
               && std::same_as<fp_kleisli_arrow_result_value_type<F, A>, B>;

}  // namespace fp::internal::meta::kleisli

#endif  // __FP_INTERNAL_META_KLEISLI_H
