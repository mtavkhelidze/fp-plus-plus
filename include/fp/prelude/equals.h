#ifndef FP_TRAITS_EQUALS_H
#define FP_TRAITS_EQUALS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/eq.h>

namespace fp::prelude {

template <template <typename> typename F, typename A>
constexpr auto equals(const F<A>& lhs, const F<A>& rhs) -> bool {
    return fp::core::types::Eq<F>::eq(lhs, rhs);
}

}  // namespace fp::prelude

#endif  // FP_TRAITS_EQUALS_H
