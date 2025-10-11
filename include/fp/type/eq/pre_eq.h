#ifndef FP_TYPE_EQ_PRE_EQ_H
#define FP_TYPE_EQ_PRE_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/type/eq/class_eq.h>

namespace fp::prelude {

template <template <typename> typename F, typename A>
constexpr auto equals(const F<A>& lhs, const F<A>& rhs) -> bool {
    return fp::type::classes::Eq<F>::equals(lhs, rhs);
}

}  // namespace fp::prelude

#endif  // FP_TYPE_EQ_PRE_EQ_H
