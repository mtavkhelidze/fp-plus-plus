#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_MONAD_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_MONAD_H

#include <fp/meta.h>
#include <fp/operators.h>

#include <type_traits>

namespace fp::traits::monad {
using namespace fp::meta::is_type_class_instance;
/**
 * Concept that checks if `Fn` can be applied to `T` and returns a value of
 * type `TC<U>`.
 */
template <typename Fn, typename T, template <typename> typename TC>
concept fp_kleisli_arrow = requires {
    requires fp_is_type_class_instance<
      TC<std::decay_t<std::invoke_result_t<Fn, T>>>>;
};

}  // namespace fp::traits::monad

namespace fp::traits::monad {

/**
 * Concept representing a lawful Monad, requiring `pure` and `flatMap`
 * support.
 */
template <template <typename> typename TC, typename T>
concept Monad = requires(TC<std::decay_t<T>> c, T t) {
    { pure<TC>(t) } -> std::same_as<TC<std::decay_t<T>>>;
    {
        c.flatMap([](T &&x) { return pure<TC>(x); })
    } -> std::same_as<TC<std::decay_t<T>>>;
};
}  // namespace fp::traits::monad

namespace fp::traits::monad {

template <template <typename> typename TC>
inline constexpr auto pure = []<typename T>(T &&t)
    requires(std::is_constructible_v<TC<std::decay_t<T>>, T>)
{ return TC<std::decay_t<T>>{std::forward<T>(t)}; };

/**
 * `lift`: Lifts a normal function `f` into the monadic context by applying it
 * and then wrapping the result using `pure`.
 */
template <template <typename> typename TC, typename F>
constexpr auto lift(F &&f) {
    return
      [f = std::forward<F>(f)](auto &&x) constexpr noexcept(
        noexcept(pure<TC>(f(std::forward<decltype(x)>(x))))
      ) -> decltype(auto) { return pure<TC>(f(std::forward<decltype(x)>(x))); };
};

/**
 * Kleisli composition operator. Composes two Kleisli arrows.
 */
template <typename F, typename G>
constexpr auto kleisli_compose(F &&f, G &&g) {
    return [f = std::forward<F>(f), g = std::forward<G>(g)]<typename X>(
             X &&x
           ) constexpr noexcept(noexcept(f(std::forward<X>(x)).flatMap(g))
           ) -> decltype(auto) { return f(std::forward<X>(x)).flatMap(g); };
}

/**
 *  Lifts a function `f` into the monadic context by composing it with
 * `pure<TC>`, where `TC` is the monadic type constructor.
 */
template <template <typename> typename TC>
inline constexpr auto liftM = []<typename F>(F &&f) {
    return fp::operators::dot(pure<TC>, std::forward<F>(f));
};

}  // namespace fp::traits::monad
#endif  // FP_TRAITS_MONAD_H
