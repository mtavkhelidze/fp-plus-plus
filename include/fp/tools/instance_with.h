#ifndef FP_TOOLS_INSTANCE_WITH_H
#define FP_TOOLS_INSTANCE_WITH_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/inner_type.h>

namespace fp::tools::instance_with {

namespace __internal {
    template <typename TA, typename TB>
    struct __is_instance_with {
        static constexpr bool value =
          std::same_as<TA, inner_type::fp_inner_type<TB>>;
    };
}  // namespace __internal

template <instance::UnaryInstance TA, instance::UnaryInstance TB>
inline constexpr bool fp_is_instance_with =
  __internal::__is_instance_with<std::decay_t<TA>, std::decay_t<TB>>::value;

template <typename TA, typename TB>
concept InstanceWith = fp_is_instance_with<TA, TB>;

}  // namespace fp::tools::instance_with

#endif  // FP_TOOLS_INSTANCE_WITH_H
