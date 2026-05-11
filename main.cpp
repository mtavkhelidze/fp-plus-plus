#include <fp/fp.h>

#include <iostream>

using namespace fp;

/**
 * This is here to give clang-tidy something to chew on.
 */
auto main() -> int {
    auto n = nothing;
    std::cout << n << '\n';
    return 0;
}
