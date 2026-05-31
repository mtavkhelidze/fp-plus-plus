#ifndef __FP_KERNEL_OPS_FLIP_H
#define __FP_KERNEL_OPS_FLIP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>

#include <concepts>
#include <utility>

namespace fp::kernel::ops {
// flip :: (A -> B -> C) -> B -> A -> C
template <typename Fn>
constexpr auto flip(Fn&& f) {
    return [f = std::forward<Fn>(f)]<typename B>(B&& b) -> auto {
        return
          [f, b = std::forward<B>(b)]<typename A>(A&& a) -> decltype(auto) {
              return f(std::forward<A>(a))(b);
          };
    };
}
}  // namespace fp::kernel::ops
#endif  // __FP_KERNEL_OPS_FLIP_H
