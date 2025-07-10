#ifndef FP_TRAITS_MONAD_H
#define FP_TRAITS_MONAD_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/flat_map.h>
#include <fp/traits/applicative.h>

namespace fp::traits::monad {
/// Concept representing a lawful Monad.
///
/// A Monad must:
/// - Be an Applicative (i.e. support `map` and `pure`)
/// - Support `flatMap`, which applies a function returning the same context
///
/// This models the traditional monadic structure:
/// - `pure(a)` lifts a value into the monad
/// - `flatMap(ma, f)` applies a function `f: A -> M<B>` to `ma: M<A>`
///
/// In FP++, `Applicative` implies `Functor`, and `HasFlatMap` ensures
/// proper Kleisli-style composition.
///
/// Equivalent to:
/// ```haskell
/// class Monad m where
///   return :: a -> m a
///   (>>=)  :: m a -> (a -> m b) -> m b
/// ```
template <typename TC>
concept Monad =
  traits::applicative::Applicative<TC> && tools::flat_map::HasFlatMap<TC>;
}  // namespace fp::traits::monad
#endif  // FP_TRAITS_MONAD_H
