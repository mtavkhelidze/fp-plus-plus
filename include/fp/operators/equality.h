#ifndef FP_OPERATORS_EQUALS_H
#define FP_OPERATORS_EQUALS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/prelude/equals.h>

namespace fp::operators::equality {

template <template <typename> typename F, typename A>
constexpr auto operator==(const F<A>& a, const F<A>& b) noexcept -> bool {
    return equals(a, b);
}

template <template <typename> typename F, typename A>
constexpr auto operator!=(const F<A>& a, const F<A>& b) noexcept -> bool {
    return !equals(a, b);
}

}  // namespace fp::operators::equality

#endif  // FP_OPERATORS_EQUALS_H
