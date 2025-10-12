#ifndef FP_TYPE_EQ_OPS_EQ_H
#define FP_TYPE_EQ_OPS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/type/eq/eq_pre_equals.h>
#include <fp/type/eq/eq_traits.h>

namespace fp::operators {

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

}  // namespace fp::operators

#endif  // FP_TYPE_EQ_OPS_EQ_H
