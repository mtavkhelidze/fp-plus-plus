#ifndef __FP_DATA_NOTHING_H
#define __FP_DATA_NOTHING_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <compare>
#include <ostream>
#include <string>

namespace fp::data {
struct _nothing {
    constexpr auto operator==(const _nothing&) const -> bool = default;
    constexpr auto operator<=>(const _nothing&) const
      -> std::strong_ordering = default;

    [[nodiscard]] auto to_string() const -> std::string { return {"Nothing"}; }

    friend auto operator<<(std::ostream& os, const _nothing& n)
      -> std::ostream& {
        return os << n.to_string();
    }
};
/**
 * A Unit type, () in Haskell or Unit in Scala.
 */
using Nothing = _nothing;
/**
 * A unit instance, like () in Haskell or Scala
 */
constexpr Nothing nothing = _nothing{};
}  // namespace fp::data

#endif  // __FP_DATA_NOTHING_H
