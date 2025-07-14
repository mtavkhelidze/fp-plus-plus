#ifndef FP_TRAITS_EQ_H
#define FP_TRAITS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/eq.h>

namespace fp::traits::eq {

template <template <typename> typename F>
concept HasEq = requires { typename fp::core::types::Eq<F>; };

}  // namespace fp::traits::eq

#endif  // FP_TRAITS_EQ_H
