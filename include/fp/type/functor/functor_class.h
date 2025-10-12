#ifndef FP_TYPE_FUNCTOR_FUNCTOR_CLASS_H
#define FP_TYPE_FUNCTOR_FUNCTOR_CLASS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>
#include <fp/type/value.h>

namespace fp::type::classes {

template <template <typename> typename F>
struct Functor {
    template <typename A>
    static constexpr auto map = []<typename Fn>(Fn&& f) {
        return [f = std::forward<Fn>(f)](const F<A>& fa) -> decltype(auto)
                   requires fp::traits::HasValue<F<A>>
                         && fp::traits::HasApply<F<A>>
                         && fp::tools::arrow::fp_is_arrow<Fn, A>
        {
            using Result = fp::tools::arrow::fp_arrow_result<Fn, A>;
            return F<Result>::apply(std::invoke(f, fa.value()));
        };
    };
};
}  // namespace fp::type::classes

#endif  // FP_TYPE_FUNCTOR_FUNCTOR_CLASS_H
