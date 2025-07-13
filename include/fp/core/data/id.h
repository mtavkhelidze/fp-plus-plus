#ifndef FP_CORE_DATACLASSES_ID_H
#define FP_CORE_DATACLASSES_ID_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/all.h>
#include <fp/internal/mixins/value.h>

namespace fp::core::data {

template <typename A>
struct Id : fp ::internal::mixins::value::WithValue<Id<A>> {
  private:
    using Base = fp::internal::mixins::value::WithValue<Id>;
    using Base::Base;

  public:
    template <typename Fn>
    auto map(Fn&& f) {
        return fp::core::types::Functor<Id>::map<A>(std::forward<Fn>(f))(
          static_cast<Id&&>(*this)
        );
    }

    auto equals(const Id& other) const -> bool {
        return fp::core::types::Eq<Id>::eq(*this, other);
    }
};
}  // namespace fp::core::data

#endif  // FP_CORE_DATACLASSES_ID_H
