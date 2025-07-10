#ifndef FP_PRELUDE_IDENTITY_H
#define FP_PRELUDE_IDENTITY_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

namespace fp::prelude {
/// Identity function: returns its argument unchanged.
/// `identity(x)` is equivalent to `x`.
struct __identity {
    template <typename A>
    constexpr A operator()(A value) const noexcept {
        return value;
    }
};

inline constexpr __identity identity{};
using identity_t = decltype(identity);
}  // namespace fp::prelude

#endif  // FP_PRELUDE_IDENTITY_H
