`FP++`: C++20 Functional Library
---
FP the hell out of C++

---

`FP++` is header-only library: all it needs to do is done at compile time and doesn't involve runtime type resolution, function calls or, God forbid, vtable lookups.

### Types

`FP++` normalises C++ types automatically — references, const, pointers, arrays,
and smart pointers are all handled transparently. There are a few cases
when`FP++` normalises fundamental types into STL containers. The latest complete
transformation rules are documented as executable tests in `test/src/cast.cpp`.

### Usage

Place `fp` somewhere in your include path and use it with `#include <fp/fp.h>` and `using namespace fp` in your C++ source file. Something like:

```bash
g++ -I/path/to/dir/with/fp/in/it -o main main.cpp -std=c++20 -g
```

### Development

Documentation is _incomplete_. There are some `readme`-s here and there, but the best way to understand how things work is to read sources `test/src`. Tests as documentation, so to speak.

#### Requirements

`FP++` requires a C++20-compliant compiler. It makes heavy use of C++20 features:

- **Concepts** — to constrain template parameters
- **Template specialisation and CRTP** — for zero-cost polymorphism
- **Deduction guides** — for ergonomic type inference
- **`constexpr` and `inline constexpr`** — for compile-time computation

Minimum compiler versions:
- Clang 14+
- GCC 12+

#### Library Development

If you are building on top of `FP++`, the internal meta and storage utilities are
available via their namespaces:

```cpp
using namespace fp::internal::meta;
using namespace fp::internal::storage;
```

No additional headers needed — `#include <fp/fp.h>` exposes everything.

#### Building and Testing

```bash
cmake -B build -S .
cmake --build build
ctest --test-dir build
```

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file
for details.

### Inspired By

- [*Functional Programming in Scala, Second
  Edition*](https://www.amazon.com/dp/1617290653) by Paul Chiusano and Rúnar
  Bjarnason
- [*Haskell in Depth*](https://www.amazon.com/dp/1617297572) by Vitaly
  Bragilevsky
- [*Cats*](https://typelevel.org/cats/) & [*Cats
  Effect*](https://typelevel.org/cats-effect/)
