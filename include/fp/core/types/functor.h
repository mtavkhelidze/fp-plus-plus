#ifndef FP_CORE_TYPECLASSES_FUNCTOR_H
#define FP_CORE_TYPECLASSES_FUNCTOR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>
#include <fp/tools/cast.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/rebind.h>
#include <fp/traits/value.h>

namespace fp::core::types {

template <template <typename> typename FA>
struct Functor {
    template <typename A>
    static constexpr auto map = []<typename F>(F&& f) {
        return [f = std::forward<F>(f)](auto&& fa) mutable -> decltype(auto)
                   requires fp::traits::value::HasValue<
                              std::remove_reference_t<decltype(fa)>>
                         && fp::traits::value::HasApply<
                              std::remove_reference_t<decltype(fa)>>
                         && fp::tools::arrow::fp_is_arrow<
                              F, typename std::remove_reference_t<
                                   decltype(fa)>::value_type>
        {
            using FAType = std::remove_reference_t<decltype(fa)>;
            using Inner = typename FAType::value_type;
            using Result = fp::tools::arrow::fp_arrow_result<F, Inner>;
            return FA<Result>::apply(
              std::invoke(
                std::forward<F>(f), std::forward<decltype(fa)>(fa).value()
              )
            );
        };
    };
};
}  // namespace fp::core::types

#endif  // FP_CORE_TYPECLASSES_FUNCTOR_H
