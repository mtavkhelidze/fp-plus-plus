/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_INTERNAL_META_KLEISLI_H
#define __FP_INTERNAL_META_KLEISLI_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/arrow.h>
#include <fp/internal/meta/inner_type.h>
#include <fp/internal/meta/instance.h>
#include <fp/internal/meta/outer_type.h>

#include <concepts>

namespace fp::internal::meta::kleisli {

template <template <typename> typename F, typename Fn, typename A>
    requires arrow::is_arrow<Fn, A>
inline constexpr bool is_kleisli_arrow =
  std::same_as<outer_type::outer_type<arrow::arrow_result<Fn, A>>, F<A>>;

}  // namespace fp::internal::meta::kleisli

#endif  // __FP_INTERNAL_META_KLEISLI_H
