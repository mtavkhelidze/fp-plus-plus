#ifndef FP_TRAITS_FUNCTOR_H
#define FP_TRAITS_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/tools.h>
#include <fp/traits/eq.h>

#include <concepts>

namespace fp::traits::functor {
using namespace fp::tools::arrow;
using namespace fp::tools::inner_type;
using namespace fp::tools::instance;
using namespace fp::tools::rebind;

/**
 * Functor is a type class that abstracts over type constructors that can be
 * `map`'ed over. Examples of such type constructors are `List`, `Option`, and
 * `Future`.
 */
template <typename FA, typename F>
concept Functor =
  fp_is_unary_instance<FA>
  && fp_is_arrow<F, fp_inner_type<FA>>
  && requires(FA fa, F f) {
         {
             fa.map(f)
         }
         -> std::same_as<fp_rebind<FA, fp_arrow_result<F, fp_inner_type<FA>>>>;
     };
}  // namespace fp::traits::functor

#endif  // FP_TRAITS_FUNCTOR_H
