
#ifndef FP_TRAITS_INSTANCE_H
#define FP_TRAITS_INSTANCE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/instance.h>

namespace fp::traits {

template <typename TC>
concept AnyInstance = tools::instance::fp_is_instance<TC>;

template <typename TC>
concept UnaryInstance = tools::instance::fp_is_unary_instance<TC>;

template <typename TC>
concept BinaryInstance = tools::instance::fp_is_binary_instance<TC>;

}  // namespace fp::traits

#endif  // FP_TRAITS_INSTANCE_H
