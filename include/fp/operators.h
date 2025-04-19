#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_SYNTAX_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_SYNTAX_H

#include <fp/prelude.h>
#include <fp/traits/traits.h>

#include <concepts>

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
}  // namespace fp::syntax::semigroup

namespace fp::operators::monoid {
using namespace operators::semigroup;
}  // namespace fp::syntax::monoid

namespace fp::operators::composition {

template <typename F, typename G>
constexpr auto operator*(F&& f, G&& g) {
    return prelude::dot(std::forward<F>(f), std::forward<G>(g));
}

template <typename A>
constexpr auto operator&=(std::invocable<A> auto f, A a) {
    return prelude::dollar(std::forward<decltype(f)>(f), std::forward<A>(a));
}

template <typename A>
constexpr auto operator>=(A a, auto&& f) {
    return prelude::pipe(std::forward<A>(a), std::forward<decltype(f)>(f));
}
};  // namespace fp::syntax::composition

namespace fp::operators::all {
using namespace fp::operators::composition;
using namespace fp::operators::semigroup;
using namespace fp::operators::monoid;
}  // namespace fp::syntax::all

#endif  // FP_SYNTAX_H
