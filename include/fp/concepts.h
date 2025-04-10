#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_CONCEPTS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_CONCEPTS_H

#include <concepts>

// Monoid concept
namespace fp {
template <typename T>
concept Monoid = requires(T a, T b, T c) {
    { T::empty() } -> std::same_as<T>;
    { T::combine(a, b) } -> std::same_as<T>;
};

template <Monoid M>
constexpr auto operator<=>(const M& lhs, const M& rhs) {
    return M::combine(lhs, rhs);
}

}  // namespace fp

namespace fp {

template <typename T>
concept Movable = std::is_nothrow_move_constructible_v<T>;

template <typename E>
concept Eq = requires(E a, E b) {
    { E::equals(a, b) } -> std::convertible_to<bool>;
};

template <Eq A>
constexpr auto operator==(const A& a, const A& b) -> bool {
    return A::equals(a, b);
}

template <Eq A>
constexpr auto operator!=(const A& a, const A& b) -> bool {
    return !A::equals(a, b);
}

}  // namespace fp

#endif  // FP_CONCEPTS_H
