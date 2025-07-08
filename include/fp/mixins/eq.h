#ifndef FP_MIXINS_EQ_H

#define FP_MIXINS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/mixins/value.h>

namespace fp::mixins::eq {

template <typename DataClass>
struct WithEq : fp::mixins::value::WithValue<DataClass> {
  private:
    using Base = fp::mixins::value::WithValue<DataClass>;
    using Base::Base;

  public:
    constexpr auto equals(const WithEq& other) const noexcept -> bool {
        return static_cast<const DataClass*>(this)->value()
            == static_cast<const DataClass*>(&other)->value();
    }
};
};  // namespace fp::mixins::eq

#endif  // FP_MIXINS_EQ_H
