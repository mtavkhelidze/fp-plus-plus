#include <functional>
#include <vector>
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP  // NOLINT:llvm-header-guard
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_OPS_MONOID_H
#define FP_OPS_MONOID_H

#include "../concepts.h"

namespace fp::ops::monoid {
// template <typename A, typename B, typename M>
//     requires Monoid<M>
// constexpr B foldMap(
//   const std::vector<A>& as, const M& m, const std::function<B(const A&)>& f
// );
// template <Monoid M, typename Container>
// static auto foldLeft(M initial, const Container& xs) -> M {
//     for (const auto& x : xs) { initial = M::combine(initial, x); }
//     return initial;
// }

// template <Monoid M, template <typename Container<M>>>
// static auto foldRight(M initial, const Container<M>& elements) -> M {
//     for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
//         initial = M::combine(*it, initial);
//     }
//     return initial;
// }

}  // namespace fp::ops::monoid
#endif  // FP_OPS_MONOID_H
