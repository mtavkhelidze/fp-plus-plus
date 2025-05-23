#ifndef FP_PRELUDE_DOT_H
#define FP_PRELUDE_DOT_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>

#include <utility>

namespace fp::prelude {

/// Function composition operator (similar to . in Haskell). dot(f, g) is
/// equivalent to f(g(x)).
template <typename F, typename G>
constexpr auto compose(F&& lhs, G&& rhs) noexcept {
    return [lhs = std::forward<F>(lhs), rhs = std::forward<G>(rhs)]<typename A>(
             A&& a
           ) constexpr noexcept -> decltype(auto)
               requires(
                 tools::arrow::Arrow<G, A>
                 && tools::arrow::Arrow<
                   F,                                   //
                   tools::arrow::fp_arrow_result<G, A>  //
                   >                                    //
               )
    { return lhs(rhs(std::forward<A>(a))); };
}
}  // namespace fp::prelude
#endif  // FP_PRELUDE_DOT_H
