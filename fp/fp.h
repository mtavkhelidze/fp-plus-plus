/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_FP_H
#define __FP_FP_H

#pragma once

#define FP_PLUS_PLUS_INCLUDED_FROM_FP_FP 1

#include <fp/core/core.h>
#include <fp/data/data.h>
#include <fp/internal/meta/meta.h>
#include <fp/internal/storage/storage.h>
#include <fp/kernel/mixins/mixins.h>
#include <fp/kernel/ops/ops.h>
#include <fp/kernel/traits/traits.h>
#include <fp/syntax/syntax.h>

#ifdef FP_PLUS_PLUS_TESTING
#include <fp/laws/laws.h>
#endif  // FP_PLUS_PLUS_TESTING

#undef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

// hoist those into the fp namespace
namespace fp {
using namespace fp::core;
using namespace fp::data;
using namespace fp::kernel::ops;
using namespace fp::kernel::traits;

// C++ type to FP++ type transformation tool
using fp::internal::meta::cast::cast;
}  // namespace fp

#endif  // __FP_FP_H
