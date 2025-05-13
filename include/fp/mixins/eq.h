#ifndef FP_MIXINS_EQ_H

#define FP_MIXINS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/storage_box.h>
#include <fp/internal/storage/storage_stack.h>
#include <fp/tools/cast.h>

#include <type_traits>

namespace fp::mixins::eq {
/**
 * Mixin for objects to conform with @ref{fp::traits::eq::Eq}.
 */
template <template <typename> typename DataClass, typename A>
struct WithEq {
  protected:
    // Eq
    constexpr auto equals(const WithEq& other) const noexcept -> bool {
        static_assert(
          std::equality_comparable<A>,
          "The type A must support operator== to use equals()."
        );
        return this->value() == other.value();
    }
};
};  // namespace fp::mixins::eq

#endif  // FP_MIXINS_EQ_H
