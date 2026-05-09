#ifndef __FP_INTERNAL_META_META_H
#define __FP_INTERNAL_META_META_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/arrow.h>
#include <fp/internal/meta/cast.h>
#include <fp/internal/meta/inner_type.h>
#include <fp/internal/meta/instance.h>
#include <fp/internal/meta/kleisli.h>
#include <fp/internal/meta/outer_type.h>
#include <fp/internal/meta/rebind.h>
#include <fp/internal/meta/tools.h>

namespace fp::internal::meta {
using namespace fp::internal::meta::arrow;
using namespace fp::internal::meta::cast;
using namespace fp::internal::meta::inner_type;
using namespace fp::internal::meta::instance;
using namespace fp::internal::meta::kleisli;
using namespace fp::internal::meta::outer_type;
using namespace fp::internal::meta::rebind;
using namespace fp::internal::meta::tools;
}  // namespace fp::internal::meta

#endif  // __FP_INTERNAL_META_META_H
