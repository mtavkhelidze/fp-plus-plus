#ifndef FP_DATA_BASE_WHATEVER_H
#define FP_DATA_BASE_WHATEVER_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <string>

namespace fp::data::base {
struct _whatever {
    constexpr auto operator==(const _whatever& /*unused*/) const -> bool {
        return true;
    }
    constexpr auto operator!=(const _whatever& /*unused*/) const -> bool {
        return false;
    }
    constexpr auto operator<=>(const _whatever& /*unused*/) const
      -> std::strong_ordering {
        return std::strong_ordering::equal;
    }
    auto to_string() const -> std::string { return std::string("Any"); }
    friend auto operator<<(std::ostream& os, const _whatever& n)
      -> std::ostream& {
        return os << n.to_string();
    }
};
using Whatever = _whatever;
Whatever constexpr whatever = _whatever{};
}  // namespace fp::data::base

#endif  // FP_DATA_BASE_WHATEVER_H
