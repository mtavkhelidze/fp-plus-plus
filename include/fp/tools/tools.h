#ifndef FP_TOOLS_H
#define FP_TOOLS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp::fp.h>
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/nothing.h>
#include <fp/tools/arrow.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/instance.h>
#include <fp/tools/instance_with.h>
#include <fp/tools/make_pair.h>
#include <fp/tools/rebind.h>

namespace fp::tools::all {
using namespace arrow;
using namespace inner_type;
using namespace instance_with;
using namespace instance;
using namespace make_pair;
using namespace rebind;
}  // namespace fp::tools::all
#endif  // FP_TOOLS_H
