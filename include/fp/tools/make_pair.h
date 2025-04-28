#ifndef FP_TOOLS_MAKE_PAIR_H
#define FP_TOOLS_MAKE_PAIR_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/instance.h>

#include <utility>

namespace fp::tools::make_pair {

namespace __internal {
    template <typename T>
    struct __make_pair_type {};

    template <template <typename, typename> typename TC, typename A, typename B>
    struct __make_pair_type<TC<A, B>> {
        using first = std::decay_t<A>;
        using second = std::decay_t<B>;
    };
}  // namespace __internal

template <typename T>
using fp_make_pair_type = std::pair<
  typename __internal::__make_pair_type<std::decay_t<T>>::first,
  typename __internal::__make_pair_type<std::decay_t<T>>::second>;
}  // namespace fp::tools::make_pair

#endif  // FP_TOOLS_MAKE_PAIR_H
