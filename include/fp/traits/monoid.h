#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_MONOID_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_MONOID_H

#include <concepts>

namespace fp::traits::monoid {
/**
 * Monoid extends the power of \ref Semigroup by providing an additional empty
 * value.
 */
template <template <typename> typename M, typename A>
concept Monoid = requires(M<A> ma, A a, A b) {
    { ma.empty() } -> std::same_as<A>;
    { ma.combine(a, b) } -> std::same_as<A>;
};

/**
 * Monoid combine oparator.
 */
template <template <typename> typename M, typename A>
    requires Monoid<M, A>
constexpr auto plus(const M<A>& lhs, const A& rhs) -> A {
    return M<A>::combine(lhs, rhs);
}

}  // namespace fp::traits::monoid

#endif  // FP_TRAITS_MONOID_H
