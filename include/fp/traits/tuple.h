#ifndef FP_TRAITS_TUPLE_H
#define FP_TRAITS_TUPLE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/tuple.h>

namespace fp::traits {

template <typename T>
concept IsTuple = tools::tuple::fp_is_tuple<T>;
}  // namespace fp::traits

#endif  // FP_TRAITS_TUPLE_H
