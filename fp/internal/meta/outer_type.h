#ifndef __FP_INTERNAL_META_OUTER_TYPE_H
#define __FP_INTERNAL_META_OUTER_TYPE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/inner_type.h>

namespace fp::internal::meta::outer_type {

namespace {
    template <typename T>
    struct __outer_type_struct {};

    template <template <typename...> typename F, typename... A>
    struct __outer_type_struct<F<A...>> {
        template <typename... Args>
        using f_alias = F<Args...>;
    };
}  // namespace

template <typename FA>
using outer_type = typename __outer_type_struct<FA>::template f_alias<
  inner_type::inner_type<FA>>;

}  // namespace fp::internal::meta::outer_type

#endif  //  __FP_INTERNAL_META_OUTER_TYPE_H
