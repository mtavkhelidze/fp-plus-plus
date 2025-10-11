#ifndef FP_TOOLS_ALL_H
#define FP_TOOLS_ALL_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/cast.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/instance.h>
#include <fp/tools/rebind.h>

namespace fp::tools {
using namespace cast;
using namespace inner_type;
using namespace instance;
using namespace rebind;
}  // namespace fp::tools
#endif  // FP_TOOLS_ALL_H
