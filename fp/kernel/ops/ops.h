#ifndef __FP_KERNEL_OPS_OPS_H
#define __FP_KERNEL_OPS_OPS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/ops/always.h>
#include <fp/kernel/ops/as.h>
#include <fp/kernel/ops/compose.h>
#include <fp/kernel/ops/discard.h>
#include <fp/kernel/ops/fmap.h>
#include <fp/kernel/ops/fproduct.h>
#include <fp/kernel/ops/id.h>  // no tests, just works
#include <fp/kernel/ops/lift.h>
#include <fp/kernel/ops/pure.h>

#endif  // __FP_KERNEL_OPS_OPS_H
