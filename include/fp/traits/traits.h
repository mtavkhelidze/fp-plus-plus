#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_TRAITS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_TRAITS_H

#include <fp/traits/applicative.h>
#include <fp/traits/eq.h>
#include <fp/traits/functor.h>
#include <fp/traits/monoid.h>
#include <fp/traits/semigroup.h>

namespace fp::traits::all {
using namespace applicative;
using namespace eq;
using namespace functor;
using namespace monoid;
using namespace semigroup;
}  // namespace fp::traits::all
#endif  // FP_TRAITS_TRAITS_H
