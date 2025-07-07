#ifndef FP_MIXINS_MAP_H

#define FP_MIXINS_MAP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/storage.h>

namespace fp::mixins::map {

template <template <typename> typename DataClass, typename A>
struct WithMap {
    template <typename F>
        requires tools::storage::HasValue<DataClass<A>>
              && tools::storage::HasApply<
                   DataClass,
                   decltype(std::declval<F>()(std::declval<A>()))>
    [[nodiscard]] constexpr auto map(F&& f) const {
        using Result = decltype(std::forward<F>(f)(std::declval<A>()));
        return DataClass<Result>::apply(
          std::forward<F>(f)(static_cast<const DataClass<A>&>(*this).value())
        );
    }
};

}  // namespace fp::mixins::map

#endif  // FP_MIXINS_MAP_H
