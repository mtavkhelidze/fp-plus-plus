#ifndef FP_FP_H
#define FP_FP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#define FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include "data/data.h"
#include "operators.h"
#include "prelude.h"
#include "tools.h"
#include "traits/traits.h"

#ifdef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#undef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

namespace fp {
using namespace data::all;
using namespace prelude;
}  // namespace fp
#endif  // FP_FP_H
