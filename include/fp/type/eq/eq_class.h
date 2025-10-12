#ifndef FP_TYPE_CLASS_EQ_H
#define FP_TYPE_CLASS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/type/value.h>

namespace fp::type::classes {
/**
 * Eq typeclass for unary type constructors like Id, Option, etc. Provides
 * Eq<F>::equals<A> -> bool
 */
template <template <typename> typename F>
struct Eq {
    template <typename A>
        requires fp::traits::HasValue<F<A>>
    static constexpr auto equals(const F<A>& a1, const F<A>& a2) -> bool {
        return a1.value() == a2.value();
    }
};

}  // namespace fp::type::classes
#endif  // FP_TYPE_CLASS_EQ_H
