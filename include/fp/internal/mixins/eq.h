#ifndef FP_MIXINS_EQ_H

#define FP_MIXINS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/traits/value.h>

namespace fp::mixins::eq {

template <class DataClass>
struct WithEq {
    [[nodiscard]] constexpr auto equals(const DataClass& other) const noexcept
      -> bool {
        static_assert(
          fp::traits::value::HasValue<DataClass>,
          "WithEq requires DataClass to implement .value()"
        );
        return static_cast<const DataClass*>(this)->value() == other.value();
    }
};

};  // namespace fp::mixins::eq

#endif  // FP_MIXINS_EQ_H
