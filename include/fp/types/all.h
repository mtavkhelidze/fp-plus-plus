#ifndef FP_TYPES_ALL_H
#define FP_TYPES_ALL_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/instance.h>
#include <fp/tools/rebind.h>

namespace fp::types::__ {
using fp::tools::arrow::Arrow;
using fp::tools::arrow::fp_arrow_result;
using fp::tools::inner_type::fp_inner_type;
using fp::tools::instance::UnaryInstance;
using fp::tools::rebind::fp_rebind;
}  // namespace fp::types::__

namespace fp::types {

template <__::UnaryInstance F>
struct Functor {
    template <
      __::Arrow<__::fp_inner_type<F>> Fn,
      typename B = __::fp_arrow_result<Fn, __::fp_inner_type<F>>>
    static auto map(const F& fa, Fn&& f) -> __::fp_rebind<F, B>;
};

}  // namespace fp::types
#endif  // FP_TYPES_ALL_H
