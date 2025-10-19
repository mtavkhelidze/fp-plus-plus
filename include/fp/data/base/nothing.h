#ifndef FP_DATA_BASE_NOTHING_H
#define FP_DATA_BASE_NOTHING_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <string>

namespace fp::data::base {
struct _nothing {
    constexpr auto operator==(const _nothing& /*unused*/) const -> bool {
        return true;
    }
    constexpr auto operator!=(const _nothing& /*unused*/) const -> bool {
        return false;
    }
    constexpr auto operator<=>(const _nothing& /*unused*/) const
      -> std::strong_ordering {
        return std::strong_ordering::equal;
    }
    // NOLINTBEGIN(readability-convert-member-functions-to-static)
    [[nodiscard]] auto to_string() const -> std::string { return {"Nothing"}; }
    // NOLINTEND(readability-convert-member-functions-to-static)
    friend auto operator<<(std::ostream& os, const _nothing& n)
      -> std::ostream& {
        return os << n.to_string();
    }
};
using Nothing = _nothing;
Nothing constexpr nothing = _nothing{};
}  // namespace fp::data::base

#endif  // FP_DATA_BASE_NOTHING_H
