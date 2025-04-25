#ifndef FP_PRELUDE_H
#define FP_PRELUDE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/nothing.h>
#include <fp/prelude/defs.h>
#include <fp/prelude/dollar.h>
#include <fp/prelude/dot.h>
#include <fp/prelude/flip.h>
#include <fp/prelude/identity.h>
#include <fp/prelude/pipe.h>
#include <fp/prelude/pure.h>

namespace fp::prelude {
using namespace fp::data::nothing;
using namespace fp::tools::tc;
}  // namespace fp::prelude
#endif  // FP_PRELUDE_H
