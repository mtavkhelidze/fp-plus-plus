#ifndef __FP_KERNEL_MIXINS_WITH_APPLICATIVE_H
#define __FP_KERNEL_MIXINS_WITH_APPLICATIVE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/ops/ops.h>
#include <fp/kernel/traits/traits.h>

namespace fp::kernel::mixins::applicative {

template <typename FA>
struct WithApplicative {
    template <typename FFn>
    auto ap(FFn&& ff) -> auto
        requires kernel::traits::HasPure<FA>
              && internal::meta::arrow::is_arrow<
                   internal::meta::inner_type::inner_type<FFn>,
                   internal::meta::inner_type::inner_type<FA> >

    {
        return kernel::ops::ap(std::forward<FFn>(ff))(
          static_cast<FA const&>(*this)
        );
    }
};
}  // namespace fp::kernel::mixins::applicative
#endif  // __FP_KERNEL_MIXINS_WITH_APPLICATIVE_H
