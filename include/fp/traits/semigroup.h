#include <type_traits>
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_SEMIGROUP_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_SEMIGROUP_H

#include <concepts>

namespace fp::traits::semigroup {
/**
 * If a type A can form a Semigroup it has an associative binary operation.
 */
template <typename S>
concept Semigroup = requires(S a, S b) {
    { combine(a, b) } -> std::same_as<S>;
};

}  // namespace fp::traits::semigroup

#endif  // FP_TRAITS_SEMIGROUP_H
