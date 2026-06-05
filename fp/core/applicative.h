/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#ifndef __FP_CORE_APPLICATIVE_H
#define __FP_CORE_APPLICATIVE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/functor.h>
#include <fp/internal/meta/meta.h>
#include <fp/kernel/traits/is_functor.h>

namespace fp::core {

template <template <typename> typename F>
    requires kernel::traits::IsFunctor<F>
struct Applicative {
    template <typename Fn>
    static auto ap(const F<Fn>& ff) {
        return [ff]<typename A>(const F<A>& fa) -> decltype(auto)
                   requires(internal::meta::arrow::is_arrow<Fn, A>)
        {
            using B = internal::meta::arrow::arrow_result<Fn, A>;
            using BC = internal::meta::cast::cast<B>;
            return Functor<F>::map([&f = ff.value()](const A& a) -> BC {
                return std::invoke(f, a);
            })(fa);
        };
    }
};

}  // namespace fp::core
#endif  // __FP_CORE_APPLICATIVE_H
