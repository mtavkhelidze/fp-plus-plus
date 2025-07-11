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
template <typename F, typename Fn>
    requires tools::arrow::Arrow<Fn, tools::inner_type::fp_inner_type<F>>
constexpr static auto fmap(F&& fa, Fn&& f) {
    if constexpr (requires {
                      fp::types::Functor<std::remove_cvref_t<F>>::map(fa, f);
                  }) {
        return fp::types::Functor<std::remove_cvref_t<F>>::map(
          std::forward<F>(fa), std::forward<Fn>(f)
        );
    } else if constexpr (requires { fa.map(f); }) {
        return std::forward<F>(fa).map(std::forward<Fn>(f));
    } else {
        static_assert(
          sizeof(F) == 0,
          "fmap: No suitable Functor instance or .map() found for given type"
        );
    }
}

}  // namespace fp::prelude
#endif  // FP_PRELUDE_FMAP_H
