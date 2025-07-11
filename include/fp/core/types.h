#ifndef FP_CORE_TYPES_H
#define FP_CORE_TYPES_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>
#include <fp/tools/cast.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/rebind.h>
#include <fp/tools/value.h>

namespace fp::core::types {

template <typename FA>
    requires fp::tools::value::HasValue<FA> && fp::tools::value::HasApply<FA>
struct Functor {
    static constexpr auto map(FA&& fa) {
        return [&]<typename F>(F&& f)
            requires fp::tools::arrow::fp_is_arrow<
              F, fp::tools::inner_type::fp_inner_type<FA>>
        {
            using Inner = typename FA::value_type;
            using Result = fp::tools::arrow::fp_arrow_result<F, Inner>;
            using Rebind = fp::tools::rebind::fp_rebind<
              FA, fp::tools::cast::fp_cast<Result>>;
            return Rebind::apply(std::invoke(std::forward<F>(f), fa.value()));
        };
    }
};
}  // namespace fp::core::types

namespace fp::core::types {
template <typename A>
    requires fp::tools::value::HasValue<A>
struct Eq {
    static constexpr auto equals(A&& a1, A&& a2) -> bool {
        return a1.value() == a2.value();
    }
};

}  // namespace fp::core::types
#endif  // FP_CORE_TYPES_H
