#include <fp/fp.h>

#include <iostream>
#include <ranges>
#include <type_traits>
#include <vector>

using namespace fp;

// struct Int {
//     Box<int> value;

//   public:
//     Int(int v) noexcept : value(Box(v)) {}
//     Int(const Int& other) noexcept : value(Box(*other.value.getOrNull())) {}

//     static auto empty() -> Int { return Int(0); }
//     static auto combine(const Int& a, const Int& b) -> Int {
//         return Int{*a.value.getOrNull() + *b.value.getOrNull()};
//     }
// };
// static_assert(Monoid<Int>, "IntMonoid<int> does not satisfy Monoid concept");
auto main() -> int {
    //
    return 0;
}
