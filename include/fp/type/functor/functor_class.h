#ifndef FP_TYPE_FUNCTOR_FUNCTOR_CLASS_H
#define FP_TYPE_FUNCTOR_FUNCTOR_CLASS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/base/traits.h>
#include <fp/tools/all.h>
#include <fp/type/classes.h>

#include <type_traits>

namespace fp::type::classes {

struct Functor {
    template <typename FA>
    static constexpr auto map(FA& fa)
        requires traits::HasApply<std::decay_t<decltype(fa)>>
    {
        using A = tools::fp_inner_type<FA>;
        return [fa]<typename Fn>(const Fn& fn)
            requires traits::Arrow<Fn, A, tools::fp_arrow_result<Fn, A>>
                  && traits::HasApply<FA>
        {
            using B = tools::fp_arrow_result<Fn, A>;
            using G = tools::fp_rebind<FA, B>;
            return G::apply(std::invoke(fn, fa.value()));
        };
    };
};
}  // namespace fp::type::classes

#endif  // FP_TYPE_FUNCTOR_FUNCTOR_CLASS_H
