#ifndef FP_TYPE_FUNCTOR_FUNCTOR_TRAITS_H
#define FP_TYPE_FUNCTOR_FUNCTOR_TRAITS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/base/prelude.h>
#include <fp/base/traits.h>
#include <fp/tools/all.h>
#include <fp/type/functor/functor_class.h>

namespace fp::traits {

template <template <typename> typename F>
concept IsFunctor = requires { Functor<F>; };

template <typename FA, typename Fn = prelude::identity_t>
concept HasMap =
  traits::HasValue<FA>
  && traits::IsArrow<Fn, tools::fp_inner_type<FA>>
  && requires(FA self, Fn f) {
         {
             self.map(f)
         } -> std::same_as<tools::fp_rebind<
           FA, tools::fp_arrow_result<Fn, tools::fp_inner_type<FA>>>>;
     };

template <typename FA, typename Fn = prelude::identity_t>
constexpr bool HasFunctor = HasMap<FA, Fn>;

}  // namespace fp::traits

#endif  // FP_TYPE_FUNCTOR_FUNCTOR_TRAITS_H
