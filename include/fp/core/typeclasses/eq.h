#ifndef FP_CORE_TYPECLASSES_EQ_H
#define FP_CORE_TYPECLASSES_EQ_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/value.h>

namespace fp::core::typeclasses {
template <typename A>
    requires fp::tools::value::HasValue<A>
struct Eq {
    static constexpr auto equals(A&& a1, A&& a2) -> bool {
        return a1.value() == a2.value();
    }
};

}  // namespace fp::core::typeclasses
#endif  // FP_CORE_TYPECLASSES_EQ_H
