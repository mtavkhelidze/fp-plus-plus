#ifndef FP_CORE_ID_H
#define FP_CORE_ID_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types.h>
#include <fp/mixins/value.h>

#include <utility>

namespace fp::core {

template <typename A>
struct Id : fp::mixins::value::WithValue<Id<A>> {
  private:
    using Base = fp::mixins::value::WithValue<Id>;
    using Base::Base;

  public:
    template <typename Fn>
    auto map(Fn&& f) {
        return fp::core::types::Functor<Id>::map(static_cast<Id&&>(*this))(
          std::forward<Fn>(f)
        );
    }
};
}  // namespace fp::core

#endif  // FP_CORE_ID_H
