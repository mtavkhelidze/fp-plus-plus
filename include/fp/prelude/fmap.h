#ifndef FP_PRELUDE_FMAP_H
#define FP_PRELUDE_FMAP_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/arrow.h>
#include <fp/tools/inner_type.h>
#include <fp/traits/functor.h>

namespace fp::prelude {

/// Generic `fmap` for any Functor.
/// Applies function `f` to the contents of `fa`.
/// Equivalent to `fa.map(f)` but in free function form.
template <traits::functor::Functor FA, typename F>
    requires tools::arrow::Arrow<F, tools::inner_type::fp_inner_type<FA>>
constexpr static auto fmap(FA&& fa, F&& f) {
    return std::forward<FA>(fa).map(std::forward<F>(f));
}

}  // namespace fp::prelude
#endif  // FP_PRELUDE_FMAP_H
