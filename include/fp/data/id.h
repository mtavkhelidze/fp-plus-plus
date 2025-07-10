#ifndef FP_DATA_MONAD_ID_H
#define FP_DATA_MONAD_ID_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/mixins/flat_map.h>
#include <fp/mixins/map.h>
#include <fp/mixins/value.h>

namespace fp::data::monad::id {

/// The Identity monad.
///
/// A minimal wrapper around a single value. Useful as a baseline Monad that
/// does nothing, but allows testing and use of generic Monad, Functor, and
/// Applicative abstractions.
///
/// `Id<A>`:
/// - is a Functor (`map`)
/// - is an Applicative (`pure` via `apply`)
/// - is a Monad (`flatMap`)
///
/// Algebraically, this models the identity function: `Id(a).map(f) == Id(f(a))`

template <typename A>
struct Id
    : fp::mixins::value::WithValue<Id<A>>
    , fp::mixins::map::WithMap<Id<A>>
    , fp::mixins::flat_map::WithFlatMap<Id<A>> {
  private:
    using Base = fp::mixins::value::WithValue<Id>;
    using Base::Base;
};

}  // namespace fp::data::monad::id

#endif  // FP_DATA_MONAD_ID_H
