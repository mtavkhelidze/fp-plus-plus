<!--
 Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 SPDX-License-Identifier: MIT
-->

# FP++ Styleguide

## Naming Conventions

### Type Parameters

| Kind                        | Convention       | Examples            |
| --------------------------- | ---------------- | ------------------- |
| Simple type                 | Capitals from A  | `A`, `B`, `C`       |
| Typeclass                   | Capitals from F  | `F`, `G`, `H`       |
| Typeclass instance          | Typeclass + type | `FA`, `FB`, `FC`    |
| Function                    | `*n`             | `Fn`, `Gn`, `Hn`    |
| Typeclass function instance | Two capitals     | `FFn`, `FGn`, `GFn` |

### Concepts / Traits

* `Is*<F>` — takes type constructor, checks structural property: `IsFunctor<F>`,
 `IsApplicative<F>`, `IsMonad<F>`
* `Has*<FA>` — takes instantiated type, checks method surface:  `HasMap<FA>`,
 `HasAp<FA>`, `HasFlatMap<FA>`
* `With*<FA>` — mixin name, CRTP base providing method implementations:
 `WithPure<FA>`, `WithFunctor<FA>`, `WithApplicative<FA>`

### Free Functions

* camelCase, verb-first: `flatMap`, `fmap`, `andThen`, `zipWith`
* Exception — short mathematical primitives stay lowercase: `ap`, `pure`, `flip`, `lift`, `curry`

### Core Structs

* PascalCase, noun: `Functor<F>`, `Applicative<F>`, `Monad<F>`

### Law Structs
* `SomethingLaws` — always a struct
* `Something` can be a typeclass, a free function, or an operator:
   - `FunctorLaws`, `MonadLaws`
   - `FlipLaws`, `ComposeLaws`, `PipeLaws`

## Namespaces

| Namespace            | Purpose                         |
| -------------------- | ------------------------------- |
| `fp::core`           | Typeclass structs               |
| `fp::kernel::ops`    | Free functions                  |
| `fp::kernel::traits` | Concepts                        |
| `fp::kernel::mixins` | CRTP mixins                     |
| `fp::internal::meta` | Type machinery — not public API |
| `fp::laws`           | Law structs                     |

## Include Guards

* `__FP_*` — internal, do not define or manipulate externally
* `FP_*` — public, user-facing feature flags, e.g. `FP_PLUS_PLUS_TESTING`

## Internal Helpers

* `__name` in anonymous namespace — private implementation detail, not part of
  public API
* Do not reference or manipulate anything prefixed with `__`

## Function Arguments

* `const&` for container args
* `&&` + `std::forward` for function args

## Constraints

* Concept constraints on free function templates go into `requires` clause, not
  into template parameter list
* Constraints on lambda bodies go in trailing `requires` on the inner lambda, not
  on the outer
* Check constraints on **unwrapped** functions, not wrapped containers — as early
  as possible

## Comments

* Every op/function gets a Haskell-style type signature comment:
    ```cpp
    // flatMap :: Monad F => (A -> F<B>) -> F<A> -> F<B>
    // curry  :: ((A, B) -> C) -> A -> B -> C
    // flip :: (A -> B -> C) -> B -> A -> C
    ```
* All other comments if not one-liners are /* block */

## General Principles

* Laws use free functions (`kernel::ops::`), not `core::` structs directly
* No redundant `Has*` traits for derivatives — if `HasAp<FA>` is satisfied,
  `WithApplicative` guarantees the rest
* `is_sparrow` (A -> B -> C) is enforced transitively: `is_arrow` in the outer
  call + `is_arrow` in `fmap` compose without needing `B` in scope
* Uncurried functions are not idiomatic — use `curry` to adapt them
