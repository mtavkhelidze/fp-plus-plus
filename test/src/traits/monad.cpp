#include <fp/fp.h>
#include <gtest/gtest.h>

#include <string>

#include "shorts.h"

using namespace fp::traits;

template <typename T>
struct Simple {
    T value;
    Simple(T v) : value(v) {}

    // template <typename A>
    // static auto unit(A&& a) -> Simple<std::decay_t<A>> {
    //     return Simple<std::decay_t<A>>(std::forward<A>(a));
    // }

    template <typename B>
    auto flatMap(auto&& f) -> const Simple<B> {
        return f(value);
    }
};
static_assert(Monad<Simple, int>, "Not a monad");

// using namespace fp::test;
// template <typename T>
// auto to_string(const T& t) -> mnd::Simple<std::string> {
//     return mnd::Simple<std::string>::unit(std::to_string(t));
// }

// auto simple_triple = [](int x) { return mnd::Simple<int>::unit(triple(x)); };

TEST(Monad_Simple, associativity) {
    //
    // auto m = mnd::unit(1);
}
