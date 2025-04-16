#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_DEFS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_DEFS_H

#include <cstddef>
inline constexpr std::size_t __fp_align_16 = 16;
inline constexpr std::size_t __fp_align_32 = 32;

#define FP_PACKED [[gnu::packed]]
#define FP_ALIGN_PACKED_16 alignas(__fp_align_16) FP_PACKED
#define FP_ALIGN_PACKED_32 alignas(__fp_align_32) FP_PACKED

#include <variant>

namespace fp {

using Nothing = std::monostate;  // is {}
using Unit = void;

}  // namespace fp

#endif  // FP_DEFS_H
