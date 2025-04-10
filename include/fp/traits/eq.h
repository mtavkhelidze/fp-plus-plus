#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_EQ_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_EQ_H

#include <concepts>

namespace fp::traits {

template <typename E>
concept Eq = requires(E a, E b) {
    { equals(a, b) } -> std::convertible_to<bool>;
};

template <Eq A>
constexpr auto operator==(const A& a, const A& b) -> bool {
    return equals(a, b);
}

template <Eq A>
constexpr auto operator!=(const A& a, const A& b) -> bool {
    return !equals(a, b);
}

}  // namespace fp::traits

#endif  // FP_TRAITS_EQ_H
