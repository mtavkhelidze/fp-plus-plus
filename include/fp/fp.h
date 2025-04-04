#ifndef __FP_PLUS_PLUS__
#define __FP_PLUS_PLUS__

#pragma once

#include <memory>
#include <type_traits>

namespace fp {

template <typename A>
using Unref = std::decay_t<A>;

}  // namespace fp

#include "concepts.h"
#include "functions.h"
#include "monads/option.h"
#include "syntax.h"

#endif  // __FP_PLUS_PLUS__
