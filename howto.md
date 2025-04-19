# fp++ — Functional Programming with C++20

A lightweight functional programming library for C++20 inspired by Haskell and
Cats, bringing expressive abstractions, type classes, and syntax sugar in a
principled, modular way.

---

## Folder & Namespace Structure

This library is organized to reflect the structure and spirit of Haskell, while
remaining idiomatic and practical for C++ development.

| Folder       | Namespace       | Purpose                                                                         |
|--------------|-----------------|---------------------------------------------------------------------------------|
| `operators/` | `fp::operators` | Syntactic sugar (e.g., `<<=`, `+`, `*>`, `<*>`, etc.)                           |
| `kernel/`    | `fp::kernel`    | Internal foundational components and machinery (private, like Cats' `internal`) |
| `traits/`    | `fp::traits`    | Core functional abstractions (e.g., `Functor`, `Applicative`, `Monad`, etc.)    |
| `data/`      | `fp::data`      | Type class instances (e.g., `Option`, `Either`, `Reader`, `Id`, etc.)           |
| `prelude/`   | `fp::prelude`   | Common functions (`pure`, `lift`, `identity`, etc.) reexported via `fp`         |
| `fp.h`       | `fp`            | Public API entry point; reexports from `fp::prelude` and `fp::data`             |

---

## Getting Started

```cpp
#include <fp/fp.h>

using namespace fp;

auto x = pure<Option>(42);

auto y = some(10) <<= [](auto i) {
    return pure<Option>(i + 5);
};
