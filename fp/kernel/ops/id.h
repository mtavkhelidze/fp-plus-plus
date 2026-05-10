#ifndef __FP_KERNEL_OPS_ID_H
#define __FP_KERNEL_OPS_ID_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <utility>

namespace fp::kernel::ops {

struct _id {
    template <typename A>
    constexpr auto operator()(A&& a) const noexcept -> A {
        return std::forward<A>(a);
    }
};

inline constexpr _id id{};

}  // namespace fp::kernel::ops

#endif  // __FP_KERNEL_OPS_ID_H
