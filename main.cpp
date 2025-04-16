#include <fp/fp.h>

#include <concepts>
#include <cstddef>
#include <iostream>
#include <optional>
#include <type_traits>
#include <vector>

template <typename T>
struct Maybe {};

template <typename T>
using Vector = std::vector<Maybe<T>>;

using namespace fp::meta::is_wrapped_by;

int main() {  //
    static_assert(is_wrapped_by<Vector, Maybe>, "Nope");
    return 0;
}
