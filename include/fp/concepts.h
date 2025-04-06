#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#pragma once

#include <concepts>

// Monoid concept
namespace fp {
template <typename T>
concept Monoid = requires(T a, T b, T c) {
    // Identity element must return type T
    { T::empty() } -> std::same_as<const T>;
    { T::combine(a, b) } -> std::same_as<const T>;

    // Combining with the identity should return the same element
    { T::combine(a, T::empty()) } -> std::same_as<const T>;
    { T::combine(T::empty(), b) } -> std::same_as<const T>;

    //    Associativity (implicitly checked)
    { T::combine(T::combine(a, b), c) } -> std::same_as<const T>;
};

template <Monoid M>
inline constexpr auto operator<=>(const M& lhs, const M& rhs) {
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
inline constexpr bool operator==(const A& a, const A& b) {
    return A::equals(a, b);
}

template <Eq A>
inline constexpr bool operator!=(const A& a, const A& b) {
    return !A::equals(a, b);
}

}  // namespace fp
