#ifndef FP_TRAITS_H
#define FP_TRAITS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

// #include <fp/traits/applicative.h>
// #include <fp/traits/monad.h>
// #include <fp/traits/semigroup.h>
#include <fp/traits/arrow.h>
#include <fp/traits/eq.h>
#include <fp/traits/functor.h>
#include <fp/traits/instance.h>
#include <fp/traits/semigroupal.h>
#include <fp/traits/tuple.h>
#include <fp/traits/value.h>

namespace fp::traits {
// using namespace applicative;
// using namespace monad;
// using namespace semigroup;
using namespace eq;
using namespace functor;
using namespace instance;
using namespace semigroupal;
using namespace tuple;
using namespace value;
}  // namespace fp::traits
#endif  // FP_TRAITS_H
