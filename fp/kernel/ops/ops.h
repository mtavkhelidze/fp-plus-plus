/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_KERNEL_OPS_OPS_H
#define __FP_KERNEL_OPS_OPS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/ops/always.h>
#include <fp/kernel/ops/andThen.h>
#include <fp/kernel/ops/ap.h>
#include <fp/kernel/ops/as.h>
#include <fp/kernel/ops/compose.h>
#include <fp/kernel/ops/discard.h>
#include <fp/kernel/ops/dollar.h>
#include <fp/kernel/ops/extract.h>
#include <fp/kernel/ops/flip.h>
#include <fp/kernel/ops/fmap.h>
#include <fp/kernel/ops/fproduct.h>
#include <fp/kernel/ops/identity.h>  // no tests, just works
#include <fp/kernel/ops/lift.h>
#include <fp/kernel/ops/map2.h>
#include <fp/kernel/ops/pipe.h>
#include <fp/kernel/ops/product.h>
#include <fp/kernel/ops/pure.h>
#include <fp/kernel/ops/zip.h>

#endif  // __FP_KERNEL_OPS_OPS_H
