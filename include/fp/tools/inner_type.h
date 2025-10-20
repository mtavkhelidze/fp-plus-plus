#ifndef FP_TOOLS_INNER_TYPE_H
#define FP_TOOLS_INNER_TYPE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/instance.h>

#include <concepts>
#include <type_traits>

namespace fp::tools::inner_type {

namespace _internal {
    template <typename F>
    struct _extract_inner_type {};

    template <template <typename> typename F, typename A>
    struct _extract_inner_type<F<A>> {
        using type = std::decay_t<A>;
    };
}  // namespace _internal

/// If given F<A>, access A
template <typename F>
    requires instance::fp_is_unary_instance<F>
using fp_inner_type =
  typename _internal::_extract_inner_type<std::decay_t<F>>::type;

template <typename F, typename A>
    requires instance::fp_is_unary_instance<F>
inline constexpr bool fp_is_inner_type = std::same_as<fp_inner_type<F>, A>;

template <typename FA, typename FB>
    requires(instance::fp_is_unary_instance<FA>
             && instance::fp_is_unary_instance<FB>)
inline constexpr bool fp_is_same_inner_type = std::
  same_as<fp_inner_type<std::decay_t<FA>>, fp_inner_type<std::decay_t<FB>>>;

}  // namespace fp::tools::inner_type

#endif  // FP_TOOLS_INNER_TYPE_H
