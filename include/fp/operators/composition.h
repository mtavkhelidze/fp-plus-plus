#ifndef FP_OPERATORS_COMPOSITION_H
#define FP_OPERATORS_COMPOSITION_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/prelude/compose.h>
#include <fp/prelude/dollar.h>
#include <fp/prelude/pipe.h>

#include <utility>

namespace fp::operators::composition {

/// Alias for fp::prelude::dollar
inline constexpr auto operator&=(auto&& f, auto&& a) noexcept {
    return fp::prelude::dollar(
      std::forward<decltype(f)>(f), std::forward<decltype(a)>(a)
    );
}
/// Alias for fp::prelude::compose
inline constexpr auto operator*(auto&& f, auto&& g) noexcept {
    return fp::prelude::compose(
      std::forward<decltype(f)>(f), std::forward<decltype(g)>(g)
    );
}
/// Reverse of fp::prelude::compose, like | in Haskell
inline constexpr auto operator|(auto&& f, auto&& g) noexcept {
    return fp::prelude::compose(
      std::forward<decltype(g)>(g), std::forward<decltype(f)>(f)
    );
}
};  // namespace fp::operators::composition

#endif  // FP_OPERATORS_COMPOSITION_H
