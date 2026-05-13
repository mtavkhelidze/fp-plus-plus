#ifndef __FP_KERNEL_WITH_FUNCTOR_H
#define __FP_KERNEL_WITH_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/ops/fmap.h>
#include <fp/kernel/traits/traits.h>

namespace fp::kernel::mixins::functor {

template <typename FA>
struct WithFunctor {
    auto map(auto&& f) const -> auto
        requires kernel::traits::HasApply<FA>
    {
        return kernel::ops::fmap(std::forward<decltype(f)>(f))(
          static_cast<FA const&>(*this)
        );
    }
};
}  // namespace fp::kernel::mixins::functor
#endif  // __FP_KERNEL_WITH_FUNCTOR_H
