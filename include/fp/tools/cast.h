#ifndef FP_TOOLS_TC_H
#define FP_TOOLS_TC_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/nothing.h>
#include <fp/internal/storage/box.h>

#include <type_traits>

namespace fp::tools::cast {
template <typename T>
using fp_cast = typename fp::internal::storage::box::Box<std::decay_t<T>>::kind;
}
#endif  // FP_TOOLS_TC_H
