#ifndef FP_TRAITS_APPLICATIVE_H
#define FP_TRAITS_APPLICATIVE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/prelude.h>
#include <fp/tools.h>
#include <fp/traits/functor.h>

#include <concepts>
#include <type_traits>
#include <utility>

namespace fp::traits::applicative {
using namespace fp::prelude;
using namespace fp::tools::all;
using namespace fp::traits::functor;

template <template <typename> typename FA, typename A>
    requires(UnaryInstance<FA<std::decay_t<A>>>)
constexpr auto pure(A&& a) -> FA<std::decay_t<A>> {
    using T = std::decay_t<A>;
    return FA<T>::apply(std::forward<A>(a));
}
/**
 * Applicative extends @ref{Functor} with `an` ap and `pure` method.
 */
template <template <typename> typename FA, typename A, typename B>
concept Applicative = fp_is_unary_instance<FA<A>>
                   && Functor<FA<A>, identity_t>
                   && requires(FA<A> fa, FA<B> fb, A a) {
                          { pure<FA>(a) } -> std::same_as<FA<A>>;
                          //   {
                          //       FA<::product(fa, fb)
                          //   } -> std::same_as<fp_rebind<FA, std::pair<A,
                          //   B>>>;
                      };

}  // namespace fp::traits::applicative

#endif  // FP_TRAITS_APPLICATIVE_H
