#ifndef FP_MIXINS_ALL_H
#define FP_MIXINS_ALL_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/mixins/eq.h>
#include <fp/mixins/value.h>

namespace fp::mixins {
using namespace eq;
using namespace value;
}  // namespace fp::mixins

#endif  // FP_MIXINS_ALL_H
