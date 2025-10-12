#ifndef FP_TYPE_FUNCTOR_FUNCTOR_PRE_FMAP_H
#define FP_TYPE_FUNCTOR_FUNCTOR_PRE_FMAP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/inner_type.h>
#include <fp/type/functor/functor_class.h>

namespace fp::prelude {
inline constexpr auto fmap = []<typename Fn>(Fn&& f) -> auto {
    return
      [f = std::forward<Fn>(f)]<template <typename> typename F, typename A>(
        const F<A>& fa
      ) -> decltype(auto) {
          return type::classes::Functor<F>::template map<A>(f)(fa);
      };
};

}  // namespace fp::prelude
#endif  // FP_TYPE_FUNCTOR_FUNCTOR_PRE_FMAP_H
