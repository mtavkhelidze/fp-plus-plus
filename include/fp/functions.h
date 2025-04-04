#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#pragma once

namespace fp {

inline const auto id = [](const auto x) { return x; };

}  // namespace fp
