#ifndef FP_MIXINS_MAP_H

#define FP_MIXINS_MAP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>
#include <fp/tools/cast.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/rebind.h>
#include <fp/tools/value.h>

namespace fp::mixins::map {

template <typename DataClass>
struct WithMap {
    template <typename F>
        requires tools::value::HasValue<DataClass>
              && tools::value::HasApply<DataClass>
              && tools::arrow::
                   Arrow<F, tools::inner_type::fp_inner_type<DataClass>>
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

}  // namespace fp::mixins::map

#endif  // FP_MIXINS_MAP_H
