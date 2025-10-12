#ifndef FP_TYPE_EQ_MIXINS_EQ_H
#define FP_TYPE_EQ_MIXINS_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/type/eq/eq_pre_equals.h>

namespace fp::mixins {

template <template <typename> typename F, typename A>
struct WithEq {
    [[nodiscard]] constexpr auto equals(const F<A>& other) const noexcept
      -> bool {
        return fp::type::classes::Eq<F>::equals(
          static_cast<const F<A>&>(*this), other
        );
    }
};

}  // namespace fp::mixins

#endif  // FP_TYPE_EQ_MIXINS_EQ_H
