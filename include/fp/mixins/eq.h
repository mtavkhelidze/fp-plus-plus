#ifndef FP_MIXINS_EQ_H

#define FP_MIXINS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/storage.h>

namespace fp::mixins::eq {

template <typename TC>
concept HasValue = fp::tools::storage::HasValue<TC>;

/**
 * Mixin for objects to conform with @ref{fp::traits::eq::Eq}.
 */
template <typename DataClass>
struct WithEq {
  public:
    // Eq
    constexpr auto equals(const WithEq& other) const noexcept {
        // static_assert(
        //   std::equality_comparable<A>,
        //   "The type A must support operator== to use equals()."
        // );
        return static_cast<const DataClass*>(this)->value()
            == static_cast<const DataClass*>(&other)->value();
    }
};
};  // namespace fp::mixins::eq

#endif  // FP_MIXINS_EQ_H
