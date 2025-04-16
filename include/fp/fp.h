#pragma once
#ifndef FP_FP_H
#define FP_FP_H

#ifdef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_PLUS_PLUS_TESTING
#error \
  "FP_PLUS_PLUS_INCLUDED_FROM_FP_FP should only be defined by including fp/fp.h. Check include order or macros."
#endif  // FP_PLUS_PLUS_TESTING
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#define FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include "defs.h"
// keep defs on top
#include "functions.h"
#include "meta.h"
#include "operators.h"
#include "syntax.h"
#include "traits/traits.h"

namespace fp {
using namespace fp::traits;
using namespace fp::operators;
}  // namespace fp
#endif  // FP_FP_H
