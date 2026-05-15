#ifndef __FP_KERNEL_TRAITS_IS_FUNCTOR_H
#define __FP_KERNEL_TRAITS_IS_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/functor.h>
#include <fp/data/data.h>
#include <fp/internal/meta/meta.h>

#include <concepts>

namespace fp::kernel::traits {
template <template <typename> typename F>
concept IsFunctor = IsWithPure<F> && requires(F<data::Any<>> fa) {
    core::Functor<F>::map([](auto x) -> auto { return x; })(fa);
};

template <typename FA, typename Fn = decltype([](auto x) -> auto { return x; })>
concept HasMap =
  internal::meta::instance::is_instance<FA>
  && HasPure<FA>
  && internal::meta::arrow::
    is_arrow<Fn, internal::meta::inner_type::inner_type<FA>>
  && requires(FA fa, Fn fn) {
         {
             fa.map(fn)
         } -> std::same_as<internal::meta::rebind::rebind<
           FA, internal::meta::cast::cast<internal::meta::arrow::arrow_result<
                 Fn, internal::meta::inner_type::inner_type<FA>>>>>;
     };
}  // namespace fp::kernel::traits

#endif  // __FP_KERNEL_TRAITS_IS_FUNCTOR_H
