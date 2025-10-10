#ifndef FP_TRAITS_SEMIGROUPAL_H
#define FP_TRAITS_SEMIGROUPAL_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/semigroupal.h>

#include <concepts>

namespace fp::traits {

template <template <typename...> typename F>
concept HasSemigroupal = requires { typename fp::core::types::Semigroupal<F>; };

template <template <typename...> typename F>
concept IsSemigroupal = HasSemigroupal<F> && requires(F<int> fa) {
    { fa.product(fa) } -> std::same_as<F<fp::core::types::Tuple<int, int>>>;
};

}  // namespace fp::traits

#endif  // FP_TRAITS_SEMIGROUPAL_H
