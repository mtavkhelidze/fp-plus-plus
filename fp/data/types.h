#ifndef __FP_DATA_TYPES_H
#define __FP_DATA_TYPES_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <array>
#include <cstddef>
#include <string>
#include <tuple>
#include <vector>

namespace fp::data {
template <typename... Ts>
using Tuple = std::tuple<Ts...>;

using String = std::string;

template <typename A>
using Vector = std::vector<A>;

template <typename A, std::size_t N>
using Array = std::array<A, N>;

}  // namespace fp::data

#endif  // __FP_DATA_TYPES_H
