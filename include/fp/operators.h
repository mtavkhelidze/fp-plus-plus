#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#include "prelude.h"
#ifndef FP_SYNTAX_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_SYNTAX_H

#include <fp/traits/traits.h>

using namespace fp::prelude::all;

namespace fp::operators::semigroup {
using namespace traits::semigroup;

template <Semigroup M>
constexpr auto operator+(M&& lhs, M&& rhs) {
    return combine(std::forward<M>(lhs), std::forward<M>(rhs));
}

template <Semigroup M>
constexpr auto operator+(const M& lhs, const M& rhs) {
    return combine(lhs, rhs);
}
}  // namespace fp::operators::semigroup

namespace fp::operators::monoid {
using namespace operators::semigroup;
}  // namespace fp::operators::monoid

namespace fp::operators::composition {

template <typename F, typename G>
constexpr auto operator*(F&& f, G&& g) {
    return dot(std::forward<F>(f), std::forward<G>(g));
}

template <typename A>
constexpr auto operator&=(std::invocable<A> auto f, A a) {
    return dollar(std::forward<decltype(f)>(f), std::forward<A>(a));
}

template <typename A>
constexpr auto operator>=(A a, auto&& f) {
    return pipe(std::forward<A>(a), std::forward<decltype(f)>(f));
}
};  // namespace fp::operators::composition

namespace fp::operators::all {
using namespace fp::operators::composition;
using namespace fp::operators::semigroup;
using namespace fp::operators::monoid;
}  // namespace fp::operators::all

#endif  // FP_SYNTAX_H
