#ifndef FP_FP_H
#define FP_FP_H
#ifdef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error \
  "FP_PLUS_PLUS_INCLUDED_FROM_FP_FP should only be defined by including fp/core.h. Check include order or macros."
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#define FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include "defs.h"
// keep defs on top
#include "box.h"
#include "functions.h"
#include "syntax.h"
#include "traits/traits.h"

namespace fp {
using namespace fp::traits;
}
#endif  // FP_FP_H
