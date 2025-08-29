#ifndef FP_TOOLS_FLAT_MAP_H
#define FP_TOOLS_FLAT_MAP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/prelude/identity.h>
#include <fp/prelude/pure.h>
#include <fp/tools/arrow.h>
#include <fp/tools/cast.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/rebind.h>
#include <fp/traits/value.h>

namespace fp::traits::flat_map {

template <typename T>
using cast = fp::tools::cast::fp_cast<T>;

template <typename TC>
using inner_type = fp::tools::inner_type::fp_inner_type<TC>;

template <typename TC, typename A>
using rebind = fp::tools::rebind::fp_rebind<TC, A>;

template <typename F, typename A>
using kleisli_result = tools::arrow::fp_kleisli_arrow_result<F, A>;

template <typename TC, typename F>
concept HasFlatMap = fp::traits::value::HasApply<TC>
                  && fp::traits::value::HasValue<TC>
                  && fp::tools::arrow::KleisliArrow<F, inner_type<TC>>
                  && requires(TC self, F f) {
                         {
                             self.flatMap(f)
                         } -> std::same_as<kleisli_result<F, inner_type<TC>>>;
                     };
}  // namespace fp::traits::flat_map
#endif  // FP_TOOLS_FLAT_MAP_H
