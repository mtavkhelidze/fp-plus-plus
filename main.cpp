#include <fp/fp.h>

#include <iostream>

using namespace fp;

/**
 * This is here to give clang-tidy something to chew on.
 */
auto main() -> int {
    // ^ vs | precedence
    auto x = 1 ^ 2 | 3;
    // if ^ first: (1^2)|3 = 3|3 = 3
    // if | first: 1^(2|3) = 1^3 = 2
    std::cout << "1 ^ 2 | 3 = " << x << "\n";

    // ^ vs * precedence
    auto y = 1 ^ 2 * 3;
    // if ^ first: (1^2)*3 = 3*3 = 9
    // if * first: 1^(2*3) = 1^6 = 7
    std::cout << "1 ^ 2 * 3 = " << y << "\n";
}
