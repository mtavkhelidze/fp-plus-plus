#ifndef __FP_PLUS_PLUS__
#define __FP_PLUS_PLUS__
#pragma once

#include <variant>

namespace fp {

using Nothing = std::monostate;  // is {}
using Unit = void;

}  // namespace fp

#include "concepts.h"
#include "functions.h"
#include "monads/option.h"
#include "syntax.h"

#endif  // __FP_PLUS_PLUS__
