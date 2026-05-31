#ifndef __FP_KERNEL_TRAITS_IS_APPLICATIVE_H
#define __FP_KERNEL_TRAITS_IS_APPLICATIVE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/applicative.h>
#include <fp/data/types.h>
#include <fp/kernel/ops/identity.h>
#include <fp/kernel/traits/is_functor.h>

namespace fp::kernel::traits {

template <template <typename> typename F>
concept IsApplicative =
  IsFunctor<F>
  && requires(
    F<data::Unit> fa, F<decltype([](data::Unit a) -> auto { return a; })> ff
  ) { core::Applicative<F>::ap(ff)(fa); };

template <typename FA>
concept HasAp =
  HasMap<FA>
  && requires(
    FA fa, internal::meta::rebind::rebind<FA, decltype(ops::identity)> ff
  ) { fa.ap(ff); };

}  // namespace fp::kernel::traits
#endif  // __FP_KERNEL_TRAITS_IS_APPLICATIVE_H
