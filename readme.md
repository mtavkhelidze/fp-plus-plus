C++23 Functional Programming Experiments
---

## Prerequisites
* You only need fp from the include directory.
* Use at your own risk. :)

## Installation
1. Clone this repository.
2. Copy `include/fp` directory into your include path.
3. Use `#include <fp/fp>`
4. Compile with a C++23-compliant compiler.
    * C++20 might also work.

## Building and Testing

```bash
cmake -B build -S .
cmake --build build
ctest --test-dir build
```

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
