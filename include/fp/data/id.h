#ifndef FP_DATA_MONAD_ID_H
#define FP_DATA_MONAD_ID_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/mixins/map.h>
#include <fp/mixins/value.h>

namespace fp::data::monad::id {

template <typename TC>
using WithValue = mixins::value::WithValue<TC>;

template <typename A>
struct Id : WithValue<Id<A>> {
  private:
    using Base = WithValue<Id>;
    using Base::Base;
};

}  // namespace fp::data::monad::id

// #ifdef FP_PLUS_PLUS_TESTING
// #include <fp/traits/traits.h>
// namespace {
// using namespace fp::data::monad::id;
// using namespace fp::prelude;
// using namespace fp::tools::all;
// using namespace fp::traits::all;

// static_assert(Eq<Id<int>>);
// static_assert(Functor<Id<int>, identity_t>);
// static_assert(Applicative<Id, int, int>);
// }  // namespace

// #endif  // FP_PLUS_PLUS_TESTING

#endif  // FP_DATA_MONAD_ID_H
