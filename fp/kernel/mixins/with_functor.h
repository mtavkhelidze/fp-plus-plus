#ifndef __FP_KERNEL_WITH_FUNCTOR_H
#define __FP_KERNEL_WITH_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/ops/ops.h>
#include <fp/kernel/traits/traits.h>

namespace fp::kernel::mixins::functor {

template <typename FA>
struct WithFunctor {
    auto map(auto&& f) const -> auto
        requires kernel::traits::HasPure<FA>
    {
        return kernel::ops::fmap(std::forward<decltype(f)>(f))(
          static_cast<FA const&>(*this)
        );
    }

    // derivatives
    auto as(auto&& b) const -> decltype(auto) {
        return ops::as(std::forward<decltype(b)>(b))(
          static_cast<FA const&>(*this)
        );
    }

    auto discard() const -> decltype(auto) {
        return ops::discard(static_cast<FA const&>(*this));
    }

    auto fproduct(auto&& f) const -> decltype(auto) {
        return ops::fproduct(std::forward<decltype(f)>(f))(
          static_cast<FA const&>(*this)
        );
    }
};
}  // namespace fp::kernel::mixins::functor
#endif  // __FP_KERNEL_WITH_FUNCTOR_H
