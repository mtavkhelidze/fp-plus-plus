#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_DEFS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_DEFS_H

#include <cstddef>

inline constexpr size_t FP_PLUS_PLUS_ALIGN = 16;
#define FP_PLUS_PLUS_PACKED __attribute__((packed))
#define FP_PLUS_PLUS_ALIGN_PACKED \
    __attribute__((aligned(FP_PLUS_PLUS_ALIGN))) __attribute__((packed))

#include <variant>

namespace fp {
template <typename T>
struct is_std_array : std::false_type {};
template <typename U, std::size_t N>
struct is_std_array<std::array<U, N>> : std::true_type {};

template <typename T>
constexpr bool is_std_array_v = is_std_array<T>::value;
}  // namespace fp

namespace fp {

using Nothing = std::monostate;  // is {}
using Unit = void;

}  // namespace fp

#endif  // FP_DEFS_H
