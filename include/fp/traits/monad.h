#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_MONAD_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_MONAD_H

#include <concepts>
#include <type_traits>

#include "guards.h"

namespace fp::traits::monad {

template <typename Fn, typename T, template <typename> typename Container>
concept kleisli_arrow = requires {
    typename std::invoke_result_t<Fn, T>;
    requires fp::traits::guards::is_instance_of<
      Container, std::decay_t<std::invoke_result_t<Fn, T>>>;
};

}  // namespace fp::traits::monad

namespace fp::traits::monad {

template <typename F, template <typename> typename M, typename A, typename B>
concept FlatMapUnary =
  std::invocable<F, A> && !std::is_reference_v<B> &&
  std::same_as<std::invoke_result_t<F, A>, M<std::decay_t<B>>>;

template <template <typename> typename M, typename A>
concept HasApply = std::is_nothrow_constructible_v<M<A>, A>;

template <template <typename> typename M, typename A>
concept HasUnit = HasApply<M, A> && requires(A a) {
    { M<A>::unit(a) } -> std::convertible_to<M<std::decay_t<A>>>;
};

template <template <typename> typename M, typename F, typename A, typename B>
concept HasFlatMap = HasUnit<M, A> && requires(M<A> m, F f) {
    FlatMapUnary<F, M, A, B>;
    { m.flatMap(f) } -> std::same_as<M<std::decay_t<B>>>;
};

template <
  template <typename> typename M, typename F, typename A, typename B = A>
concept Monad = HasApply<M, A> && HasUnit<M, A> && HasFlatMap<M, F, A, B>;

}  // namespace fp::traits::monad

namespace fp::traits::monad {

/**
 * Kleisli composition operator for composing two functions.
 * This operator composes two Kleisli arrows `f` and `g`, returning a new
 * function.
 */
template <typename F, typename G>
constexpr auto operator>>=(F&& f, G&& g) {
    return [f = std::forward<F>(f), g = std::forward<G>(g)](
             auto x
           ) constexpr noexcept(noexcept(f(x).flatMap(g))) -> decltype(auto) {
        return f(x).flatMap(g);
    };
}

}  // namespace fp::traits::monad
#endif  // FP_TRAITS_MONAD_H
