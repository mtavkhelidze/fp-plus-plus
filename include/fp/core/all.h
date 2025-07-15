#ifndef FP_CORE_ALL_H
#define FP_CORE_ALL_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/data/all.h>
#include <fp/core/nothing.h>
#include <fp/core/types/all.h>
#include <fp/core/whatever.h>

namespace fp::core {
using namespace types;
using namespace data;
}  // namespace fp::core

#endif  // FP_CORE_ALL_H
