#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_FUNCTIONS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_FUNCTIONS_H

#include <utility>

namespace fp::__internal {
struct __identity {
    template <typename A>
    constexpr A operator()(A&& value) const noexcept {
        return std::forward<A>(value);
    }
};
}  // namespace fp::__internal

namespace fp {
inline constexpr fp::__internal::__identity identity{};
using identity_t = decltype(fp::identity);
}  // namespace fp

#endif  // FP_FUNCTIONS_H
