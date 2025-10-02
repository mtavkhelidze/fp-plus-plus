#ifndef FP_MIXINS_WITH_EQ_H
#define FP_MIXINS_WITH_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types/eq.h>

namespace fp::core::mixins {

template <template <typename> typename F, typename A>
struct WithEq {
    [[nodiscard]] constexpr auto equals(const F<A>& other) const noexcept
      -> bool {
        return fp::core::types::Eq<F>::equals(
          static_cast<const F<A>&>(*this), other
        );
    }
};

}  // namespace fp::core::mixins

#endif  // FP_MIXINS_WITH_EQ_H
