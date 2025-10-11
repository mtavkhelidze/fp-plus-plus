#ifndef FP_DATA_BASE_NOTHING_H
#define FP_DATA_BASE_NOTHING_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <string>

namespace fp::data::base {
struct __nothing {
    constexpr auto operator==(const __nothing&) const -> bool { return true; }
    constexpr auto operator!=(const __nothing&) const -> bool { return false; }
    constexpr auto operator<=>(const __nothing&) const -> std::strong_ordering {
        return std::strong_ordering::equal;
    }
    auto to_string() const -> std::string { return std::string("Nothing"); }
    friend std::ostream& operator<<(std::ostream& os, const __nothing& n) {
        return os << n.to_string();
    }
};
using Nothing = __nothing;
Nothing constexpr nothing = __nothing{};
}  // namespace fp::data::base

#endif  // FP_DATA_BASE_NOTHING_H
