#ifndef __FP_SYNTAX_DOT_OP_H
#define __FP_SYNTAX_DOT_OP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/ops/ops.h>

#include <utility>

namespace fp::syntax {
constexpr auto operator*(auto&& f, auto&& g) {
    return kernel::ops::compose(
      std::forward<decltype(f)>(f), std::forward<decltype(g)>(g)
    );
}
}  // namespace fp::syntax

#endif  // __FP_SYNTAX_DOT_OP_H
