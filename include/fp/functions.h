#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_FUNCTIONS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_FUNCTIONS_H

#include <utility>

namespace fp::functions {

inline const auto id = [](const auto x) { return x; };
struct Identity {
    template <typename T>
    constexpr auto operator()(T&& value) const noexcept -> T&& {
        return std::forward<T>(value);
    }
};

constexpr Identity identity;

}  // namespace fp::functions

#endif  // FP_FUNCTIONS_H
