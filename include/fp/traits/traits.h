#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_H

#include "eq.h"
#include "monad.h"
#include "monoid.h"

namespace fp::traits {
using namespace eq;
using namespace monad;
using namespace monoid;
}  // namespace fp::traits
#endif  // FP_TRAITS_H
