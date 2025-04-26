#ifndef FP_OPERATORS_COMPOSITION_H
#define FP_OPERATORS_COMPOSITION_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/prelude/dollar.h>
#include <fp/prelude/dot.h>
#include <fp/prelude/pipe.h>
#include <fp/tools/arrow.h>

#include <concepts>
#include <utility>

namespace fp::operators::composition {
using namespace fp::prelude;

inline constexpr auto operator&=(auto&& f, auto&& a) noexcept {
    return dollar(std::forward<decltype(f)>(f), std::forward<decltype(a)>(a));
}

template <typename F, typename G>
inline constexpr auto operator*(
  std::invocable<F> auto&& f, std::invocable<G> auto&& g
) {
    return dot(std::forward<F>(f), std::forward<G>(g));
}

template <typename A>
inline constexpr auto operator>=(A&& a, auto&& f) {
    return pipe(std::forward<A>(a), std::forward<decltype(f)>(f));
}
};  // namespace fp::operators::composition

#endif  // FP_OPERATORS_COMPOSITION_H
