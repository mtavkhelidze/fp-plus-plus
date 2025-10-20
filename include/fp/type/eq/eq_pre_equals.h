#ifndef FP_TYPE_EQ_EQ_PRE_EQUALS_H
#define FP_TYPE_EQ_EQ_PRE_EQUALS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/all.h>
#include <fp/type/classes.h>

#include <concepts>

namespace fp::prelude {

template <template <typename> typename F, typename A>
constexpr auto equals(const F<A>& lhs, const F<A>& rhs) -> bool {
    return fp::type::classes::Eq<F>::equals(lhs, rhs);
}

template <typename A>
    requires(std::equality_comparable<A>)
constexpr auto equals(const A& lhs, const A& rhs) -> bool {
    return rhs == lhs;
}

}  // namespace fp::prelude

#endif  // FP_TYPE_EQ_EQ_PRE_EQUALS_H
