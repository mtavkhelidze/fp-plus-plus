/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_KERNEL_OPS_AND_THEN_H
#define __FP_KERNEL_OPS_AND_THEN_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/ops/always.h>
#include <fp/kernel/ops/flip.h>
#include <fp/kernel/ops/identity.h>
#include <fp/kernel/ops/map2.h>

namespace fp::kernel::ops {

// @sig: andThen :: Applicative F => F<A> -> F<B> -> F<B>
constexpr auto andThen = map2(always(identity));

// @sig: before :: Applicative F => F<A> -> F<B> -> F<A>
constexpr auto before = flip(andThen);

}  // namespace fp::kernel::ops

#endif  // __FP_KERNEL_OPS_AND_THEN_H
