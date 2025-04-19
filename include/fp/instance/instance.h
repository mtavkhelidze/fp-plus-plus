#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_INSTANCE_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_INSTANCE_H

#include <fp/instance/monad/id.h>

namespace fp::instance::all {
using namespace fp::instance::monad::id;
}

#endif  // FP_INSTANCE_H
