#ifndef FP_CORE_TYPES_SEMIGROUPAL_H
#define FP_CORE_TYPES_SEMIGROUPAL_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/tuple.h>

namespace fp::core::types {

template <template <typename> class F>
struct Semigroupal {
    template <typename A, typename B>
    static auto product(const F<A>& fa, const F<B>& fb) -> F<Tuple<A, B>>;
};

}  // namespace fp::core::types
#endif  // FP_CORE_TYPES_SEMIGROUPAL_H
