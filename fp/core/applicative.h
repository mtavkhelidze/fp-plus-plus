#ifndef __FP_CORE_APPLICATIVE_H
#define __FP_CORE_APPLICATIVE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/traits/is_pure.h>

namespace fp::core {
template <template <typename> typename F>
struct Applicative {
    template <typename Fn>
    static auto ap(const F<Fn>& ff) {
        return [ff]<typename A>(const F<A>& fa) -> decltype(auto)
                   requires(
                     internal::meta::arrow::is_arrow<Fn, A>
                     && kernel::traits::HasPure<F<A>>
                   )
        {
            using B = internal::meta::arrow::arrow_result<Fn, A>;
            using BC = internal::meta::cast::cast<B>;
            return F<BC>::pure(std::invoke(ff.value(), fa.value()));
        };
    }
};
}  // namespace fp::core
#endif  // __FP_CORE_APPLICATIVE_H
