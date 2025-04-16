#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_DEFS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_DEFS_H

#include <cstddef>

inline constexpr size_t FP_PLUS_PLUS_ALIGN = 16;
#define FP_PLUS_PLUS_PACKED __attribute__((packed))
#define FP_PLUS_PLUS_ALIGN_PACKED                                        \
    __attribute__((aligned(FP_PLUS_PLUS_ALIGN))) __attribute__((packed))

#define EMIT_COMPILER_WARNING_STRINGIFY0(x) #x
#define EMIT_COMPILER_WARNING_STRINGIFY1(x) EMIT_COMPILER_WARNING_STRINGIFY0(x)
#ifdef __GNUC__
#define EMIT_COMPILER_WARNING_COMPOSE(x) GCC warning x
#else
#define EMIT_COMPILER_MESSAGE_PREFACE(type)                                 \
    __FILE__ "(" EMIT_COMPILER_WARNING_STRINGIFY1(__LINE__) "): " type ": "
#define EMIT_COMPILER_WARNING_COMPOSE(x)                      \
    message(EMIT_COMPILER_MESSAGE_PREFACE("warning C0000") x)
#endif
#define WARNING(x) \
    _Pragma(EMIT_COMPILER_WARNING_STRINGIFY1(EMIT_COMPILER_WARNING_COMPOSE(x)))

#include <variant>

namespace fp {

using Nothing = std::monostate;  // is {}
using Unit = void;

}  // namespace fp

#endif  // FP_DEFS_H
