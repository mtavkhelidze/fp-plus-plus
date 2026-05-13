#ifndef __FP_INTERNAL_META_TOOLS_H
#define __FP_INTERNAL_META_TOOLS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <concepts>
#include <type_traits>

namespace fp::internal::meta::tools {

template <typename>
constexpr bool always_false = false;

template <typename F>
constexpr bool has_no_copy = !std::is_copy_constructible_v<F>;

template <typename F>
constexpr bool has_no_move = !std::is_move_constructible_v<F>;

template <typename F, typename A>
constexpr bool has_no_direct_constructor = !std::constructible_from<F, A>;

}  //  namespace fp::internal::meta::tools

#endif  //  __FP_INTERNAL_META_TOOLS_H
