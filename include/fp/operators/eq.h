#ifndef FP_OPERATORS_EQ_H
#define FP_OPERATORS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/eq.h>
#include <fp/traits/traits.h>

namespace fp::operators::eq {

template <template <typename> typename F, typename A>
    requires traits::HasEq<F>
constexpr auto operator==(const F<A>& a, const F<A>& b) noexcept -> bool {
    return core::types::Eq<F>::equals(a, b);
}

template <template <typename> typename F, typename A>
    requires traits::HasEq<F>
constexpr auto operator!=(const F<A>& a, const F<A>& b) noexcept -> bool {
    return !core::types::Eq<F>::equals(a, b);
}

}  // namespace fp::operators::eq

#endif  // FP_OPERATORS_EQ_H
