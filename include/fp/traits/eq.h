#ifndef FP_TRAITS_EQ_H
#define FP_TRAITS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <concepts>

namespace fp::traits::eq {

template <typename E>
concept Eq = requires(E&& a, E&& b) {
    { a.equals(b) } -> std::convertible_to<bool>;
};

}  // namespace fp::traits::eq

#endif  // FP_TRAITS_EQ_H
