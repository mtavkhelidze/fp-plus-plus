#ifndef FP_TRAITS_EQ_H
#define FP_TRAITS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/eq.h>
#include <fp/core/whatever.h>

namespace fp::traits {

template <template <typename> typename F>
concept HasEq = requires { typename fp::core::types::Eq<F>; };

template <template <typename> typename F>
concept IsEq =
  HasEq<F> && requires(F<fp::core::Whatever> fa, F<fp::core::Whatever> fb) {
      { fa.equals(fb) } -> std::same_as<bool>;
  };

}  // namespace fp::traits

#endif  // FP_TRAITS_EQ_H
