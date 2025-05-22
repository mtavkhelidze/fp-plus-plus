#ifndef FP_TOOLS_APPLY_H
#define FP_TOOLS_APPLY_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/cast.h>
#include <fp/tools/inner_type.h>

#include <utility>

namespace fp::tools::storage {

template <typename TC>
concept HasValue = requires(TC tc, inner_type::fp_inner_type<TC>&& a) {
    { tc.value() } -> std::same_as<cast::fp_cast<decltype(a)>>;
};

template <template <typename> typename TC, typename A>
concept HasApply = requires(A&& a) {
    {
        TC<cast::fp_cast<A>>::apply(std::forward<A>(a))
    } -> std::same_as<TC<cast::fp_cast<A>>>;
};

}  // namespace fp::tools::storage
#endif  // FP_TOOLS_APPLY_H
