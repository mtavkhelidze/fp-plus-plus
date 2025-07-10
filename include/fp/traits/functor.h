#ifndef FP_TRAITS_FUNCTOR_H
#define FP_TRAITS_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/map.h>

#include <type_traits>

namespace fp::traits::functor {
/**
 * Functor is a type class that abstracts over type constructors that can be
 * `map'-ed over. Examples of such type constructors are `List`, `Option`, and
 * `Future`.
 */
template <typename T>
concept Functor = fp::tools::map::HasMap<std::remove_cvref_t<T>>;

}  // namespace fp::traits::functor

#endif  // FP_TRAITS_FUNCTOR_H
