#ifndef FP_CORE_ALL_H
#define FP_CORE_ALL_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/dataclasses/all.h>
#include <fp/core/typeclasses/all.h>

namespace fp::core {
using namespace typeclasses;
using namespace dataclasses;
}  // namespace fp::core

#endif  // FP_CORE_ALL_H
