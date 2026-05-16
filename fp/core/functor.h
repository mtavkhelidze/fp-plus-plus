#ifndef __FP_CORE_FUNCTOR_H
#define __FP_CORE_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/arrow.h>
#include <fp/internal/meta/cast.h>
#include <fp/kernel/traits/is_pure.h>

#include <utility>

namespace fp::core {

template <template <typename> typename F>
    requires kernel::traits::IsWithPure<F>
struct Functor {
    template <typename Fn>
    static auto map(Fn&& f) {
        return [f = std::forward<Fn>(f)]<typename A>(
                 const F<A>& fa
               ) -> decltype(auto) {
            static_assert(internal::meta::arrow::is_arrow<Fn, A>);
            using B = internal::meta::arrow::arrow_result<Fn, A>;
            using BC = internal::meta::cast::cast<B>;
            return F<BC>::pure(std::invoke(f, fa.value()));
        };
    }
};
}  // namespace fp::core
#endif  // __FP_CORE_FUNCTOR_H
