#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from "<fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_FUNCTIONS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_FUNCTIONS_H

namespace fp::functions {

inline const auto id = [](const auto x) { return x; };

}  // namespace fp::functions

#endif  // FP_FUNCTIONS_H
