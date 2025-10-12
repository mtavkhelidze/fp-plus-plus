#ifndef FP_TOOLS_INNER_TYPE_H
#define FP_TOOLS_INNER_TYPE_H

#ifndef FP_tools_INNER_TYPE_H
#define FP_tools_INNER_TYPE_H
#include <type_traits>
#include <concepts>
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/instance.h>

namespace fp::tools::inner_type {

namespace _internal {
    template <typename T>
    struct _extract_inner_type {};

    template <template <typename> typename TC, typename A>
    struct _extract_inner_type<TC<A>> {
        using type = std::decay_t<A>;
    };
}  // namespace _internal

/// If given TC<A>, access A
template <typename TC>
    requires instance::fp_is_unary_instance<TC>
using fp_inner_type =
  typename _internal::_extract_inner_type<std::decay_t<TC>>::type;

template <typename TC, typename A>
    requires instance::fp_is_unary_instance<TC>
inline constexpr bool fp_is_inner_type = std::same_as<fp_inner_type<TC>, A>;

template <typename TA, typename TB>
    requires(instance::fp_is_unary_instance<TA>
             && instance::fp_is_unary_instance<TB>)
inline constexpr bool fp_is_same_inner_type = std::
  same_as<fp_inner_type<std::decay_t<TA>>, fp_inner_type<std::decay_t<TB>>>;

}  // namespace fp::tools::inner_type

#endif  // FP_tools_INNER_TYPE_H

#endif
