#ifndef __FP_CORE_FUNCTOR_H
#define __FP_CORE_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/traits/traits.h>

namespace fp::core {
template <template <typename> typename F>
struct Functor {
    template <typename A, typename Fn>
        requires internal::meta::arrow::is_arrow<Fn, A>
              && kernel::traits::HasApply<F<A>>
    static auto map(const F<A>& fa, Fn&& f) -> decltype(auto) {
        using B = internal::meta::arrow::arrow_result<Fn, A>;
        using BC = internal::meta::cast::cast<B>;
        return F<BC>::apply(std::invoke(std::forward<Fn>(f), fa.value()));
    }
};
}  // namespace fp::core
#endif  // __FP_CORE_FUNCTOR_H
