#ifndef FP_CORE_ANY_H
#define FP_CORE_ANY_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <string>

namespace fp::core {
struct __whateve {
    constexpr auto operator==(const __whateve&) const -> bool { return true; }
    constexpr auto operator!=(const __whateve&) const -> bool { return false; }
    constexpr auto operator<=>(const __whateve&) const -> std::strong_ordering {
        return std::strong_ordering::equal;
    }
    auto to_string() const -> std::string { return std::string("Any"); }
    friend std::ostream& operator<<(std::ostream& os, const __whateve& n) {
        return os << n.to_string();
    }
};
using Whatever = __whateve;
Whatever constexpr whatever = __whateve{};
}  // namespace fp::core

#endif  // FP_CORE_ANY_H
