#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_MONOID_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_MONOID_H

#include <fp/traits/semigroup.h>

#include <concepts>

namespace fp::traits::monoid {
/**
 * Monoid extends the power of \ref Semigroup by providing an additional empty
 * value.
 */
template <typename M>
concept Monoid = traits::semigroup::Semigroup<M> && requires() {
    { M::empty() } -> std::same_as<M>;
};

}  // namespace fp::traits::monoid

#endif  // FP_TRAITS_MONOID_H
