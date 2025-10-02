#ifndef FP_MIXINS_WITH_FLAT_MAP_H
#define FP_MIXINS_WITH_FLAT_MAP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>
#include <fp/tools/inner_type.h>
#include <fp/traits/arrow.h>
#include <fp/traits/value.h>

namespace fp::core::mixins {
template <typename DataClass>
struct WithFlatMap {
    template <typename F>
        requires traits::value::HasValue<DataClass>
              && traits::arrow::
                   KleisliArrow<F, tools::inner_type::fp_inner_type<DataClass>>
    [[nodiscard]] constexpr auto flatMap(F&& f) const {
        return std::invoke(
          std::forward<F>(f), static_cast<const DataClass&>(*this).value()
        );
    }
};
}  // namespace fp::core::mixins
#endif  // FP_MIXINS_WITH_FLAT_MAP_H
