#ifndef FP_TRAITS_FUNCTOR_H
#define FP_TRAITS_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types.h>
#include <fp/prelude/identity.h>
#include <fp/tools/inner_type.h>

namespace fp::traits::functor {
template <typename F>
concept HasMap = requires(F self) {
    { self.map(fp::prelude::identity) };
};

template <typename F>
concept HasFunctor = requires { typename fp::core::types::Functor<F>; };

template <typename F>
concept IsFunctor = HasFunctor<F>;  // || HasMap<F>;
}  // namespace fp::traits::functor

#endif  // FP_TRAITS_FUNCTOR_H
