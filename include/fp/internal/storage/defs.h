#ifndef FP_INTERNAL_STORAGE_DEFS_H
#define FP_INTERNAL_STORAGE_DEFS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <cstddef>

inline constexpr std::size_t __fp_align_16 = 16;
inline constexpr std::size_t __fp_align_32 = 32;

#define FP_PACKED [[gnu::packed]]
#define FP_ALIGN_PACKED_16 alignas(__fp_align_16) FP_PACKED
#define FP_ALIGN_PACKED_32 alignas(__fp_align_32) FP_PACKED

#endif  // FP_INTERNAL_STORAGE_DEFS_H
