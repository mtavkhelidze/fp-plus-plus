#pragma once
#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#include <algorithm>
#include <array>
#include <memory>

namespace fp::util {

inline const auto id = [](const auto x) { return x; };

template <typename T, typename... Ts>
auto to_array(T&& t, Ts&&... ts) -> std::unique_ptr<T[]> {
    auto arr = std::array<T, 1 + sizeof...(Ts)>{
      std::forward<T>(t), std::forward<Ts>(ts)...
    };
    auto ptr = std::make_unique<T[]>(arr.size());
    std::copy(arr.begin(), arr.end(), ptr.get());
    return ptr;
}
}  // namespace fp::util
