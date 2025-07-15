#ifndef FP_PRELUDE_ALL_H
#define FP_PRELUDE_ALL_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/prelude/compose.h>
#include <fp/prelude/dollar.h>
#include <fp/prelude/flip.h>
// #include <fp/prelude/fmap.h>
#include <fp/prelude/identity.h>
#include <fp/prelude/pipe.h>
#include <fp/prelude/pure.h>
#include <fp/tools/cast.h>

namespace fp::prelude {
// hoist fp_cast
using namespace fp::tools::cast;
}  // namespace fp::prelude
#endif  // FP_PRELUDE_ALL_H
