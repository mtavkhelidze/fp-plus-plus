#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#pragma once

#include <variant>

namespace fp {
template <class>
inline constexpr bool is_always_false = false;

using Nothing = std::monostate;  // is {}
using Unit = void;

}  // namespace fp
