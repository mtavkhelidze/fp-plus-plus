#ifndef FP_TOOLS_INSTANCE_WITH_H
#define FP_TOOLS_INSTANCE_WITH_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/inner_type.h>

namespace fp::tools::instance_with {

using namespace fp::tools::inner_type;

namespace __internal {
    template <typename TA, typename TB>
    struct __is_instance_with {
        static constexpr bool value = std::same_as<TA, fp_inner_type<TB>>;
    };
}  // namespace __internal
using namespace fp::tools::instance_with::__internal;

template <UnaryInstance TA, UnaryInstance TB>
inline constexpr bool fp_is_instance_with =
  fp_is_unary_instance<TA>
  && fp_is_instance<TB>
  && __is_instance_with<std::decay_t<TA>, std::decay_t<TB>>::value;

template <typename TA, typename TB>
concept InstanceWith = fp_is_instance_with<TA, TB>;

}  // namespace fp::tools::instance_with

#endif  // FP_TOOLS_INSTANCE_WITH_H
