#ifndef FP_CORE_TYPES_TUPLE_H
#define FP_CORE_TYPES_TUPLE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <utility>

namespace fp::core::types {
template <typename A, typename B>
using Tuple = std::pair<A, B>;
}
#endif  // FP_CORE_TYPES_TUPLE_H
