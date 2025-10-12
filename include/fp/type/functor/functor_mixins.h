#ifndef FP_TYPE_FUNCTOR_FUNCTOR_MIXINS_H
#define FP_TYPE_FUNCTOR_FUNCTOR_MIXINS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/base/traits.h>
#include <fp/tools/all.h>
#include <fp/type/value.h>

namespace fp::mixins {

template <typename DataClass>
struct WithMap {
    template <typename F>
        requires traits::HasValue<DataClass>
              && traits::HasApply<DataClass>
              && traits::Arrow<F, tools::fp_inner_type<DataClass>>
    [[nodiscard]] constexpr auto map(F&& f) const noexcept {
        using Inner = typename DataClass::value_type;
        using Result = tools::arrow::fp_arrow_result<F, Inner>;
        using Rebind =
          tools::rebind::fp_rebind<DataClass, tools::cast::fp_cast<Result>>;
        return Rebind::apply(
          std::invoke(
            std::forward<F>(f), static_cast<const DataClass&>(*this).value()
          )
        );
    }
};

}  // namespace fp::mixins

#endif  // FP_TYPE_FUNCTOR_FUNCTOR_MIXINS_H
