#pragma once
#include <concepts>
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_OPERATORS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_OPERATORS_H

#include <fp/operators/composition.h>
#include <fp/operators/eq.h>
#include <fp/operators/semigroup.h>

namespace fp::operators {
using namespace composition;
using namespace eq;
using namespace semigroup;
}  // namespace fp::operators

#endif  // FP_OPERATORS_H
