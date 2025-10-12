#ifndef FP_TRAITS_EQ_H
#define FP_TRAITS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/instances.h>
#include <fp/type/eq/eq_class.h>

namespace fp::traits {

template <template <typename> typename F>
concept IsEq = requires { typename type::classes::Eq<F>; };

template <template <typename> typename F>
concept HasEquals =
  IsEq<F> && requires(F<data::Whatever> fa, F<data::Whatever> fb) {
      { fa.equals(fb) } -> std::same_as<bool>;
  };

}  // namespace fp::traits

#endif  // FP_TRAITS_EQ_H
