#ifndef FP_TOOLS_PAIR_H
#define FP_TOOLS_PAIR_H
#include <type_traits>
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/tuple.h>

namespace fp::tools::tuple {
namespace __internal {
    template <typename T>
    struct __is_tuple : std::false_type {};

    template <typename A, typename B>
    struct __is_tuple<fp::core::types::Tuple<A, B>> : std::true_type {};

}  // namespace __internal

template <typename T>
inline constexpr bool fp_is_tuple = __internal::__is_tuple<T>::value;

}  // namespace fp::tools::tuple
#endif  // FP_TOOLS_PAIR_H
