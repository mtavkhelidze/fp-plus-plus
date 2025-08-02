#ifndef FP_PRELUDE_TUPLE_H
#define FP_PRELUDE_TUPLE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/tuple.h>

#include <type_traits>

namespace fp::prelude {

template <typename A, typename B>
constexpr auto tuple(A&& a, B&& b)
  -> fp::core::types::Tuple<std::decay_t<A>, std::decay_t<B>> {
    return std::make_pair(std::forward<A>(a), std::forward<B>(b));
}

}  // namespace fp::prelude
#endif  // FP_PRELUDE_TUPLE_H
