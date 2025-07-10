#ifndef FP_DATA_MONAD_ID_H
#define FP_DATA_MONAD_ID_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/mixins/map.h>
#include <fp/mixins/value.h>

namespace fp::data::monad::id {

template <typename A>
struct Id
    : fp::mixins::value::WithValue<Id<A>>
    , fp::mixins::map::WithMap<Id<A>> {
  private:
    using Base = fp::mixins::value::WithValue<Id>;
    using Base::Base;
};

}  // namespace fp::data::monad::id

#endif  // FP_DATA_MONAD_ID_H
