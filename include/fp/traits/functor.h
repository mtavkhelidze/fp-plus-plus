#ifndef FP_TRAITS_FUNCTOR_H
#define FP_TRAITS_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/functor.h>
#include <fp/core/whatever.h>
#include <fp/prelude/identity.h>
#include <fp/tools/inner_type.h>
#include <fp/traits/arrow.h>

namespace fp::traits::functor {
template <template <typename> typename F>
concept HasFunctor = requires { typename fp::core::types::Functor<F>; };

template <template <typename> typename F>
concept IsFunctor = HasFunctor<F> && requires(F<fp::core::Whatever> fa) {
    { fa.map(fp::prelude::identity) } -> std::same_as<F<fp::core::Whatever>>;
};

}  // namespace fp::traits::functor

#endif  // FP_TRAITS_FUNCTOR_H
