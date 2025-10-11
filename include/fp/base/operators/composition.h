#ifndef FP_OPERATORS_COMPOSITION_H
#define FP_OPERATORS_COMPOSITION_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/base/prelude/compose.h>
#include <fp/base/prelude/dollar.h>
#include <fp/base/prelude/pipe.h>

#include <utility>

namespace fp::operators {

/// Alias for @ref{fp::prelude::dollar}
inline constexpr auto operator&=(auto&& f, auto&& a) noexcept {
    return fp::prelude::dollar(
      std::forward<decltype(f)>(f), std::forward<decltype(a)>(a)
    );
}
/// Alias for @ref{fp::prelude::compose}
inline constexpr auto operator*(auto&& f, auto&& g) noexcept {
    return fp::prelude::compose(
      std::forward<decltype(f)>(f), std::forward<decltype(g)>(g)
    );
}
/// Reverse of @ref{fp::prelude::compose}, like `|` in Haskell
inline constexpr auto operator|(auto&& f, auto&& g) noexcept {
    return fp::prelude::compose(
      std::forward<decltype(g)>(g), std::forward<decltype(f)>(f)
    );
}
};  // namespace fp::operators

#endif  // FP_OPERATORS_COMPOSITION_H
