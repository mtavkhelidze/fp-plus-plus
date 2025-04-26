#ifndef FP_OPERATORS_EQ_H
#define FP_OPERATORS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/traits/eq.h>

namespace fp::operators::eq {

template <traits::eq::Eq A>
constexpr auto operator==(const A& a, const A& b) noexcept(noexcept(a.equals(b))
) -> bool {
    return a.equals(b);
}

template <traits::eq::Eq A>
constexpr auto operator!=(const A& a, const A& b) noexcept(noexcept(a.equals(b))
) -> bool {
    return !a.equals(b);
}
}  // namespace fp::operators::eq

#endif  // FP_OPERATORS_EQ_H
