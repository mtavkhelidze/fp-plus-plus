#ifndef FP_TRAITS_MONOID_H
#define FP_TRAITS_MONOID_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/traits/semigroup.h>

#include <concepts>

namespace fp::traits::monoid {
/**
 * @brief Monoid extends the power of \ref Semigroup by providing an identity
 * element.
 *
 * The `empty` function must be a static member function returning a value of
 * type `M` since ADL won't work with arity 0.
 */
template <typename M>
concept Monoid = traits::semigroup::Semigroup<M> && requires() {
    { M::empty() } -> std::same_as<M>;
};

}  // namespace fp::traits::monoid

#endif  // FP_TRAITS_MONOID_H
