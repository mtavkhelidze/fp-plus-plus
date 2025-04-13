#include <functional>
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_MONAD_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_MONAD_H

#include <type_traits>

#include "guards.h"

using namespace fp::traits::guards;

namespace fp::traits::monad {

template <typename Fn, typename T, template <typename> typename TypeConstructor>
concept fp_kleisli_arrow = requires {
    requires fp_is_instance_of<
      TypeConstructor, std::decay_t<std::invoke_result_t<Fn, T>>>;
};

}  // namespace fp::traits::monad

namespace fp::traits::monad {

/// Wraps a raw value into the given monadic type constructor. Requires that
/// the> is constructible from T.
template <template <typename> typename TypeConstructor, typename T>
    requires fp_constructible_from<T, TypeConstructor>
constexpr auto pure(T&& val) {
    return TypeConstructor<std::decay_t<T>>{std::forward<T>(val)};
}

/// Concept representing a lawful Monad: must support `pure` and `flatMap`.
/// Requires that `pure` wraps a value and `flatMap` supports Kleisli chaining.
template <template <typename> typename TypeConstructor, typename T>
concept Monad = requires(TypeConstructor<std::decay_t<T>> c, T t) {
    {
        pure<TypeConstructor>(t)
    } -> std::same_as<TypeConstructor<std::decay_t<T>>>;
    {
        c.flatMap([](T&& x) { return pure<TypeConstructor>(x); })
    } -> std::same_as<TypeConstructor<std::decay_t<T>>>;
};
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
