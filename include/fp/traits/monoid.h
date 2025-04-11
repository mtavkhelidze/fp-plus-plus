#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_MONOID_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_MONOID_H

#include <concepts>

namespace fp::traits {

template <typename M>
concept Monoid = requires(M a, M b) {
    requires std::same_as<std::decay_t<decltype(M::empty())>, M>;
    requires std::same_as<std::decay_t<decltype(combine(a, b))>, M>;
};

template <Monoid M>
constexpr auto operator<=>(const M& lhs, const M& rhs) {
    return combine(lhs, rhs);
}

}  // namespace fp::traits

#endif  // FP_TRAITS_MONOID_H
