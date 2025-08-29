#ifndef FP_PRELUDE_PRODUCT_H
#define FP_PRELUDE_PRODUCT_H
#define FP_
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/semigroupal.h>
#include <fp/core/types/tuple.h>

namespace fp::prelude {
template <template <typename> typename F, typename A, typename B>
constexpr auto product(const F<A>& fa, const F<B>& fb)
  -> F<fp::core::types::Tuple<A, B>> {
    return fp::core::types::Semigroupal<F>::product(fa, fb);
}
}  // namespace fp::prelude
#endif  // FP_PRELUDE_PRODUCT_H
