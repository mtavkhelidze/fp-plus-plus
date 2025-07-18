#ifndef FP_TRAITS_ALL_H
#define FP_TRAITS_ALL_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

// #include <fp/traits/applicative.h>
#include <fp/traits/arrow.h>
#include <fp/traits/eq.h>
#include <fp/traits/functor.h>
#include <fp/traits/instance.h>
#include <fp/traits/value.h>
// #include <fp/traits/monad.h>
// #include <fp/traits/semigroup.h>

namespace fp::traits {
using namespace eq;
using namespace functor;
using namespace instance;
using namespace value;
}  // namespace fp::traits
#endif  // FP_TRAITS_ALL_H
