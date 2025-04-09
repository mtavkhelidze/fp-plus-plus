C++20 Functional Programming Header-Only Library
---

## Table of Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Building and Testing](#building-and-testing)
- [Useful Macros](#useful-macros)
- [License](#license)

## Prerequisites

* You only need the `fp` directory from the `include` directory.
* There are no dependencies; it just works.
* For examples of usage, take a look at the `*.cpp` files in the `test`
  directory.
* Use it at your own risk. :)

## Installation

1. Clone this repository.
2. Copy the `include/fp` directory into your include path.
3. Include the library with `#include <fp/fp.h>`.
4. Compile with a C++20-compliant compiler.

```bash
g++ -Iinclude -o fp_test main.cpp -std=c++20 -g -O0
```

## Building and Testing

```bash
cmake -B build -S .
cmake --build build
ctest --test-dir build
```

## Useful Macros

| Macro                            | Description                                                                 |
|----------------------------------|-----------------------------------------------------------------------------|
| `FP_DISABLE_RAW_POINTER_WARNING` | Disables the compile-time warning for raw pointer usage in the `Box` class. |

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file
for details.
