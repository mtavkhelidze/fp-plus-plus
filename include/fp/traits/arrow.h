#ifndef FP_TRAITS_ARROW_H
#define FP_TRAITS_ARROW_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>

namespace fp::traits::arrow {
template <typename F, typename A>
concept Arrow = fp::tools::arrow::fp_is_arrow<F, A>;
}
#endif  // FP_TRAITS_ARROW_H
