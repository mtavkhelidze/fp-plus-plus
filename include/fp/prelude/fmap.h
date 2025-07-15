#ifndef FP_PRELUDE_FMAP_H
#define FP_PRELUDE_FMAP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/functor.h>
#include <fp/tools/inner_type.h>

namespace fp::prelude {
inline constexpr auto fmap = []<typename Fn>(Fn&& f) {
    return
      [f = std::forward<Fn>(f)]<template <typename> typename F, typename A>(
        const F<A>& fa
      ) -> decltype(auto) {
          return core::types::Functor<F>::template map<A>(f)(fa);
      };
};

}  // namespace fp::prelude
#endif  // FP_PRELUDE_FMAP_H
