#ifndef __FP_PP_CONCEPTS_H__
#define __FP_PP_CONCEPTS_H__

#include <concepts>

// Monoid concept
namespace fp {

template <typename M>
concept Monoid = requires(M a, M b) {
    { M::empty() } -> std::same_as<const M>;
    { a.combine(b) } -> std::same_as<const M>;
};

template <Monoid M>
inline constexpr const M operator+(const M& lhs, const M& rhs) {
    return lhs.combine(rhs);
}

template <Monoid M>
inline constexpr M& operator+=(M& lhs, const M& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

}  // namespace fp


namespace fp {

template <typename A>
concept Eq = requires(A a, A b) {
    { a.equals(b) } -> std::convertible_to<bool>;
};

template <Eq A>
inline constexpr bool operator==(const A& a, const A& b) {
    return a.equals(b);
}

template <Eq A>
inline constexpr bool operator!=(const A& a, const A& b) {
    return !a.equals(b);
}

}  // namespace fp

#endif  // __FP_PP_CONCEPTS_H__
