#ifndef FP_MIXINS_FLAT_MAP_H
#define FP_MIXINS_FLAT_MAP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/value.h>

namespace fp::mixins::flat_map {
template <typename DataClass>
struct WithFlatMap {
    template <typename F>
        requires tools::value::HasValue<DataClass>
              && tools::arrow::
                   KleisliArrow<F, tools::inner_type::fp_inner_type<DataClass>>
    [[nodiscard]] constexpr auto flatMap(F&& f) const {
        return std::invoke(
          std::forward<F>(f), static_cast<const DataClass&>(*this).value()
        );
    }
};
}  // namespace fp::mixins::flat_map
#endif  // FP_MIXINS_FLAT_MAP_H
