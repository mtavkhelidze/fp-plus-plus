#ifndef FP_TOOLS_H
#define FP_TOOLS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp::fp.h>
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/nothing.h>
#include <fp/tools/arrow.h>
#include <fp/tools/cast.h>
#include <fp/tools/instance.h>
#include <fp/tools/instance_with.h>
#include <fp/tools/make_pair.h>
#include <fp/tools/map.h>
#include <fp/tools/rebind.h>
#include <fp/tools/value.h>

namespace fp::tools::all {
using namespace arrow;
using namespace cast;
using namespace inner_type;
using namespace instance_with;
using namespace instance;
using namespace make_pair;
using namespace map;
using namespace rebind;
using namespace value;
}  // namespace fp::tools::all
#endif  // FP_TOOLS_H
