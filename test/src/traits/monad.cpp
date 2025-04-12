#include <fp/fp.h>
#include <gtest/gtest.h>

#include <functional>
#include <string>
#include <type_traits>

#include "shorts.h"

using namespace fp::traits;
using namespace fp::syntax;
using namespace fp::test;
using namespace fp::functions;
using fp::traits::unit;

template <typename T>
struct Simple {
    T value;
};
// static_assert(HasUnit<Simple, int>);

// TEST(Monad_Simple, laws) {
//     std::function<Simple<std::string>(int)> f =
//       [](int x) -> Simple<std::string> {
//         return unit<Simple>(std::to_string(x));
//     };
//     std::function<Simple<std::string>(std::string)> g =
//       [](std::string s) -> Simple<std::string> {
//         return unit<Simple>(s + "!");
//     };

//     Simple<int> x(42);

//     // // Associativity
//     auto lhs = x.flatMap(f).flatMap(g);
//     auto rhs = x.flatMap([](auto x) { return Simple(x + 10); });
//     std::cout << "lhs: " << rhs.value << std::endl;
//     // auto rhs = x.flatMap<std::string>([&](int a) {
//     //     return f(a).flatMap<std::string>(g);
//     // });
//     // EXPECT_EQ(lhs.value, rhs.value);

//     // // // Right identity
//     // auto right_id = x.flatMap(id);
//     // EXPECT_EQ(right_id.value, x.value);

//     // // // Left identity
//     // int y = 99;
//     // auto left_id = unit<Simple>(y).flatMap(f);
//     // auto direct = f(y);
//     // EXPECT_EQ(left_id.value, direct.value);
// }
