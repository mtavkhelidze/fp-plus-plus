/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_KERNEL_OPS_FISH__H
#define __FP_KERNEL_OPS_FISH__H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/ops/extract.h>

namespace fp::kernel::ops {

// fish :: (A -> F<B>) -> (B -> F<C>) -> A -> F<C>
template <typename FFn>
constexpr auto fish(FFn&& ffn) {
    return
      [ffn =
         std::forward<FFn>(ffn)]<typename FGn>(FGn&& fgn) -> decltype(auto) {
          return [ffn, fgn]<typename A>(const A& a) -> decltype(auto)
                     requires(
                       internal::meta::arrow::is_arrow<FFn, A>
                       && internal::meta::arrow::is_arrow<
                         FGn, internal::meta::inner_type::inner_type<
                                internal::meta::arrow::arrow_result<FFn, A>>>

                     )

          { return fgn(extract(ffn(a))); };
      };
};
}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_FISH__H
