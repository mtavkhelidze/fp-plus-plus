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
    // F<A>.ap :: F<A -> B> -> F<B>
    template <typename FFn>
    auto ap(FFn&& ff) -> auto
        requires kernel::traits::HasMap<FA>
              && internal::meta::rebind::is_same_f<FA, FFn>
              && internal::meta::arrow::is_arrow<
                   internal::meta::inner_type::inner_type<FFn>,
                   internal::meta::inner_type::inner_type<FA>>

    {
        return kernel::ops::ap(std::forward<FFn>(ff))(
          static_cast<FA const&>(*this)
        );
    }

    // F<A>.map2 :: (A -> B -> C) -> F<B> -> F<C>
    template <typename FFn>
    auto map2(FFn&& ff) const -> auto {
        return kernel::ops::map2(std::forward<FFn>(ff))(
          static_cast<FA const&>(*this)
        );
    };

    // F<A>.product :: F<B> -> F<Tuple<A, B>>
    template <typename B>
    auto product(const B& b) const -> auto {
        return kernel::ops::product(static_cast<FA const&>(*this))(b);
    }

    // F<A>.zip :: F<B> -> F<Tuple<A, B>>
    template <typename FB>
    auto zip(const FB& fb) const -> auto {
        return this->product(fb);
    }

    // F<A>.zipWith :: (A -> B -> C) -> F<B> -> F<C>
    template <typename Fn>
    auto zipWith(Fn&& ff) const -> auto {
        return this->map2(ff);
    }
};
}  // namespace fp::kernel::mixins::applicative
#endif  // __FP_KERNEL_MIXINS_WITH_APPLICATIVE_H
