#ifndef __FP_KERNEL_OPS_ALWAYS_H
#define __FP_KERNEL_OPS_ALWAYS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <utility>

namespace fp::kernel::ops {
namespace {
    struct __always {
        template <typename A>
        constexpr auto operator()(A&& a) const noexcept {
            return [a = std::forward<A>(a)](auto&& /*b*/) noexcept -> auto {
                return a;
            };
        }
    };
}  // namespace
// always :: A-> B -> A
constexpr auto always = __always{};

}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_ALWAYS_H
