C++20 Functional Programming Header-Only Library
---

## Prerequisites
* You only need the `fp` directory from the `include` directory.
* There are no dependencies; it just works.
* For examples of usage, take a look at the `*.cpp` files in the `test` directory.
* Use it at your own risk. :)

## Installation
1. Clone this repository.
2. Copy the `include/fp` directory into your include path.
3. Include the library with `#include <fp/fp>`.
4. Compile with a C++20-compliant compiler.

## Building and Testing

```bash
cmake -B build -S .
cmake --build build
ctest --test-dir build
```

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
