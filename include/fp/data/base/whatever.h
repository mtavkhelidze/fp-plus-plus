#ifndef FP_DATA_BASE_WHATEVER_H
#define FP_DATA_BASE_WHATEVER_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <string>

namespace fp::data {
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
}  // namespace fp::data

#endif  // FP_DATA_BASE_WHATEVER_H
