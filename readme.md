C++20 Functional Programming Header-Only Library
---

## Table of Contents

- [Usage](#usage)
- [Installation](#installation)
- [Documentation](#docu)
- [Building and Testing](#building-and-testing)
- [License](#license)

## Usage

* You only need the `fp` directory from the `include` directory. Just copy it
  into your project and add to include path.
* There are no dependencies; it just works.
* For examples of usage, take a look at the `*.cpp` files in the `test`
  directory.
* Use it at your own risk. :)

## Installation

1. Clone this repository.
2. Copy the `fp` directory from `include` into your include path.
3. Include the library with `#include <fp/fp.h>`.
4. Compile with a C++20-compliant compiler.

```bash
g++ -Iinclude -o fp_test main.cpp -std=c++20 -g -O0
```
## Documentation

Documentation is _incomplete_.

* There is some documentation in [HOWTO](./howto.md).

```bash
cmake -B build -S .
cmake --build build
ctest --test-dir build
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file
for details.
