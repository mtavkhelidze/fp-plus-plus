#include <functional>
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_MONAD_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_MONAD_H

#include <type_traits>

#include "fp/syntax.h"
#include "fp/traits/guards.h"

using namespace fp::traits::guards;

namespace fp::traits::monad {

// Concept that checks if `Fn` can be applied to `T` and returns a value of type
// `TC<U>`.
template <typename Fn, typename T, template <typename> typename TC>
concept fp_kleisli_arrow = requires {
    requires fp_is_instance_of<TC, std::decay_t<std::invoke_result_t<Fn, T>>>;
};

}  // namespace fp::traits::monad

namespace fp::traits::monad {

/// Concept representing a lawful Monad, requiring `pure` and `flatMap` support.
template <template <typename> typename TC, typename T>
concept Monad = requires(TC<std::decay_t<T>> c, T t) {
    { pure<TC>(t) } -> std::same_as<TC<std::decay_t<T>>>;
    {
        c.flatMap([](T &&x) { return pure<TC>(x); })
    } -> std::same_as<TC<std::decay_t<T>>>;
};
}  // namespace fp::traits::monad

namespace fp::traits::monad {

// `pure`: Lifts a value into the monadic context (e.g., wraps it in `TC`).
template <template <typename> typename TC>
inline constexpr auto pure = []<typename T>(T &&t) noexcept(
                               noexcept(TC<std::decay_t<T>>{std::forward<T>(t)})
                             )
    requires fp_constructible_from<T, TC>
{ return TC<std::decay_t<T>>{std::forward<T>(t)}; };

// `lift`: Lifts a normal function `f` into the monadic context by applying it
// and then wrapping the result using `pure`.
template <template <typename> typename TC, typename F>
constexpr auto lift(F &&f) {
    return
      [f = std::forward<F>(f)](auto &&x) constexpr noexcept(
        noexcept(pure<TC>(f(std::forward<decltype(x)>(x))))
      ) -> decltype(auto) { return pure<TC>(f(std::forward<decltype(x)>(x))); };
};

// `operator>>=`: Kleisli composition operator. This function composes two
// functions `f` and `g` into one, such that `f` is applied first and `g`
// is applied to the result of `f`.
template <typename F, typename G>
constexpr auto operator>>=(F &&f, G &&g) {
    return [f = std::forward<F>(f), g = std::forward<G>(g)]<typename X>(
             X &&x
           ) constexpr noexcept(noexcept(f(std::forward<X>(x)).flatMap(g))
           ) -> decltype(auto) { return f(std::forward<X>(x)).flatMap(g); };
}

// `liftM`: Lifts a function `f` into the monadic context by composing it with
// `pure<TC>`, where `TC` is the monadic type constructor.
template <template <typename> typename TC>
inline constexpr auto liftM = []<typename F>(F &&f) {
    using fp::syntax::operator*;
    return pure<TC> * std::forward<F>(f);
};

}  // namespace fp::traits::monad
#endif  // FP_TRAITS_MONAD_H
