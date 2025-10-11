#ifndef FP_TOOLS_REBIND_H
#define FP_TOOLS_REBIND_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/instance.h>

namespace fp::tools::rebind {

namespace _internal {
    template <typename T>
    struct _rebind_instance {};

    template <template <typename> typename TC, typename A>
    struct _rebind_instance<TC<A>> {
        template <typename B>
        using type = TC<std::decay_t<B>>;
    };

    template <template <typename, typename> typename TC, typename A, typename B>
    struct _rebind_instance<TC<A, B>> {
        template <typename C, typename D>
        using type = TC<std::decay_t<C>, std::decay_t<D>>;
    };
}  // namespace _internal

/// Transform TC<A> into TC<B>
template <typename TC, typename B>
    requires(instance::fp_is_unary_instance<TC>)
using fp_rebind =
  typename _internal::_rebind_instance<std::decay_t<TC>>::template type<B>;

/// Transform TC<A, B> into TC<C, D>
template <typename TC, typename C, typename D>
    requires(instance::fp_is_binary_instance<TC>)
using fp_rebind_binary =
  typename _internal::_rebind_instance<std::decay_t<TC>>::template type<C, D>;

}  // namespace fp::tools::rebind

#endif  // FP_TOOLS_REBIND_H
