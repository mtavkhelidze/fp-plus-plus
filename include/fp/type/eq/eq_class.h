#ifndef FP_TYPE_EQ_EQ_CLASS_H
#define FP_TYPE_EQ_EQ_CLASS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/type/value.h>

#include <concepts>

namespace fp::type::classes {
/**
 * Eq typeclass for unary type constructors like Id, Option, etc. Provides
 * Eq<F>::equals<A> -> bool
 */
template <template <typename> typename F>
struct Eq {
    // 1. Container WithValue
    template <typename A>
        requires(traits::HasValue<F<A>>)
    static constexpr auto equals(const F<A>& a1, const F<A>& a2) -> bool {
        return a1.value() == a2.value();
    }

    // 2. Concrete types with ==
    template <typename A>
    static constexpr auto equals(const A& a1, const A& a2) -> bool
        requires(std::equality_comparable<A>)
    {
        return a1 == a2;
    }
};

}  // namespace fp::type::classes

#endif  // FP_TYPE_EQ_EQ_CLASS_H
