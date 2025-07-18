#ifndef FP_CORE_TYPECLASSES_FUNCTOR_H
#define FP_CORE_TYPECLASSES_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>
#include <fp/traits/value.h>

namespace fp::core::types {

template <template <typename> typename F>
struct Functor {
    template <typename A>
    static constexpr auto map = []<typename Fn>(Fn&& f) {
        return [f = std::forward<Fn>(f)](const F<A>& fa) -> decltype(auto)
                   requires fp::traits::value::HasValue<F<A>>
                         && fp::traits::value::HasApply<F<A>>
                         && fp::tools::arrow::fp_is_arrow<Fn, A>
        {
            using Result = fp::tools::arrow::fp_arrow_result<Fn, A>;
            return F<Result>::apply(std::invoke(f, fa.value()));
        };
    };
};
}  // namespace fp::core::types

#endif  // FP_CORE_TYPECLASSES_FUNCTOR_H
