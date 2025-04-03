#ifndef __FP_PP_CONCEPTS_H__
#define __FP_PP_CONCEPTS_H__

#include <concepts>
namespace fp {

template <typename A>
concept Eq = requires(A a, A b) {
    { a.equals(b) } -> std::convertible_to<bool>;
};

template <typename M>
concept Monoid = requires(M a, M b) {
    { M::empty() } -> std::same_as<const M>;
    { a.combine(b) } -> std::same_as<const M>;
};

}  // namespace fp

#endif  // __FP_PP_CONCEPTS_H__
