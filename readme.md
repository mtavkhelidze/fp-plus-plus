## C++20 Functional Programming Header-Only Library

## Table of Contents

- [Usage](#usage)
- [Type Naming Conventions](#type-naming-conventions)
- [Installation](#installation)
- [Documentation](#documentation)
- [Building and Testing](#building-and-testing)
- [License](#license)

## Usage

- You only need the `fp` directory from the `include` directory. Just copy it
  into your project and add to include path.
- There are no dependencies; it just works.
- For examples of usage, take a look at the `*.cpp` files in the `test`
  directory.
- Use it at your own risk. :)

## Type Naming Conventions

FP++ uses specific conventions for naming types to improve code clarity and consistency:

- `T` denotes a raw C++ type, such as `const int&` or `double*`.
- `A` represents a normalized FP type, which is typically a wrapped or adapted version of a raw type.
- `F` stands for type constructors, which are templates or higher-kinded types that produce types when applied.
- `Fn` usually indicates a unary arrow (function).

## Installation

1. Clone this repository.
2. Copy the `fp` directory from `include` into your include path.
3. Include the library with `#include <fp/fp.h>`.
4. Compile with a C++20-compliant compiler.

```bash
g++ -Iinclude -o fp_test main.cpp -std=c++20 -g -O0
```

## Documentation

Documentation is _incomplete_. Most of the readme files are totally bogus.

## Building and Testing

```bash
cmake -B build -S .
cmake --build build
ctest --test-dir build
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file
for details.
