#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_APPLICATIVE_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_APPLICATIVE_H

#include <fp/functions.h>
#include <fp/tools.h>
#include <fp/traits/functor.h>

#include <concepts>
#include <type_traits>
#include <utility>

namespace fp::traits::applicative {
using namespace fp::tools::arrow;
using namespace fp::tools::inner_type;
using namespace fp::tools::instance;
using namespace fp::tools::rebind;
using namespace fp::traits::functor;

template <template <typename> typename FA, typename A>
    requires(UnaryInstance<FA<A>>)
constexpr auto pure(A&& a) -> FA<std::decay_t<A>> {
    return FA<std::decay_t<A>>::apply(std::forward<std::decay_t<A>>(a));
}
/**
 * Applicative extends @ref{Functor} with `an` ap and `pure` method.
 */
template <template <typename> typename FA, typename A, typename B>
concept Applicative = fp_is_unary_instance<FA<A>>
                   && Functor<FA<A>, fp::identity_t>
                   && requires(FA<A> fa, FA<B> fb, A a) {
                          { pure<FA>(a) } -> std::same_as<FA<A>>;
                          //   {
                          //       FA<::product(fa, fb)
                          //   } -> std::same_as<fp_rebind<FA, std::pair<A,
                          //   B>>>;
                      };

}  // namespace fp::traits::applicative

#endif  // FP_TRAITS_APPLICATIVE_H
