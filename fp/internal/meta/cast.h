#ifndef __FP_INTERNAL_META_CAST_H
#define __FP_INTERNAL_META_CAST_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/box.h>

#include <type_traits>

namespace fp::internal::meta::cast {
template <typename T>
using cast = typename fp::internal::storage::Box<std::decay_t<T>>::kind;
}  // namespace fp::internal::meta::cast

#endif  // __FP_INTERNAL_META_CAST_H
