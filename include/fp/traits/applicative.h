#ifndef FP_TRAITS_APPLICATIVE_H
#define FP_TRAITS_APPLICATIVE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/traits/functor.h>

namespace fp::traits::applicative {

/// In FP++, `Functor` (defined via `HasMap`) implies the presence of
/// `HasApply`. This means any Functor also supports the `pure` operation via
/// `HasApply`. Therefore, every Functor in FP++ is also an Applicative by
/// construction.
///
/// The chain is:
/// - `HasApply` requires the type to have an `apply` static method for `pure`
/// - `HasMap` requires `HasApply` and `map` method
/// - `Functor` concept is defined as `HasMap`
///
/// This ensures that the free function `pure<DataClass>(x)` works for all
/// Functors, making Functor and Applicative concepts overlap in FP++.
template <typename T>
concept Applicative = traits::functor::Functor<T>;

}  // namespace fp::traits::applicative

#endif  // FP_TRAITS_APPLICATIVE_H
