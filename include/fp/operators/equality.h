#ifndef FP_OPERATORS_EQUALS_H
#define FP_OPERATORS_EQUALS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/prelude/equals.h>
#include <fp/traits/has_eq.h>

namespace fp::operators::equality {

template <template <typename> typename F, typename A>
    requires fp::traits::HasEq<F>
constexpr auto operator==(const F<A>& a, const F<A>& b) noexcept -> bool {
    return prelude::equals(a, b);
}

template <template <typename> typename F, typename A>
    requires fp::traits::HasEq<F>
constexpr auto operator!=(const F<A>& a, const F<A>& b) noexcept -> bool {
    return !prelude::equals(a, b);
}

}  // namespace fp::operators::equality

#endif  // FP_OPERATORS_EQUALS_H
