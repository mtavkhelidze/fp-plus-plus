/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_LAWS_FUNCTOR_LAWS_H
#define __FP_LAWS_FUNCTOR_LAWS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/data.h>
#include <fp/internal/meta/meta.h>
#include <fp/kernel/ops/ops.h>
#include <fp/kernel/traits/traits.h>

namespace fp::laws {

template <template <typename> typename F>
    requires kernel::traits::IsFunctor<F>
struct FunctorLaws {
    template <typename A>
    static auto identity(const F<A>& fa) -> bool {
        return kernel::ops::fmap(kernel::ops::identity)(fa).value()
            == fa.value();
    }

    template <typename A>
    static auto composition(const F<A>& fa, auto& f, auto& g)
        requires(
          internal::meta::arrow::is_arrow<decltype(f), A>
          && internal::meta::arrow::is_arrow<
            decltype(g),
            internal::meta::arrow::arrow_result<decltype(f), A>>
        )
    {
        return kernel::ops::fmap(g)(kernel::ops::fmap(f)(fa)).value()
            == kernel::ops::fmap([&](const A& x) -> auto {
                   return g(f(x));
               })(fa)
                 .value();
    }
};
}  // namespace fp::laws

#endif  // __FP_LAWS_FUNCTOR_LAWS_H
