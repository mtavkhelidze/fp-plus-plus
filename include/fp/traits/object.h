#ifndef FP_TRAITS_OBJECT_H
#define FP_TRAITS_OBJECT_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools.h>

namespace fp::traits::object {
using namespace fp::tools::instance;
using namespace fp::tools::inner_type;

template <typename TC, typename A>
inline constexpr bool fp_is_not_constructible =
  fp_is_unary_instance<TC>
  && fp_has_no_direct_constructor<TC, A>
  && fp_has_no_copy<TC>
  && fp_has_no_move<TC>;

template <typename TC>
inline constexpr bool fp_is_object = requires {
    typename fp_inner_type<TC>;
    requires(fp_is_not_constructible<TC, fp_inner_type<TC>>);
    { TC::apply(std::declval<fp_inner_type<TC>>()) } -> std::same_as<TC>;
};

template <typename TC>
concept Object = fp_is_object<TC>;

}  // namespace fp::traits::object
#endif  // FP_TRAITS_OBJECT_H
