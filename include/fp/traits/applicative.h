#ifndef FP_TRAITS_APPLICATIVE_H
#define FP_TRAITS_APPLICATIVE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/prelude/identity.h>
#include <fp/tools/all.h>
#include <fp/traits/functor.h>

namespace fp::traits::applicative {
using namespace fp::prelude;
using namespace fp::tools::all;
using namespace fp::traits::functor;
/**
 * Applicative extends @ref{Functor} with `an` ap and `pure` method.
 */
template <template <typename> typename FA, typename A, typename B>
concept Applicative = fp_is_unary_instance<FA<A>>
                   && Functor<FA<A>, identity_t>
                   && requires(FA<A> fa, FA<B> fb, A a) {
                          { pure<FA>(a) } -> std::same_as<FA<A>>;
                      };

}  // namespace fp::traits::applicative

#endif  // FP_TRAITS_APPLICATIVE_H
