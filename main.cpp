#include <concepts>
#include <functional>
#include <iostream>
#include <type_traits>

#include "fp/fp.h"

template <typename T>
struct MyMonad;

template <typename T>
MyMonad<T> unit(T a);

template <template <typename> typename M, typename A, typename B = A>
concept Monad = requires(M<A> m, A a, std::function<M<B>(A)> f) {
    { unit(a) } -> std::same_as<M<A>>;
    { m.flatMap(f) } -> std::same_as<decltype(f(a))>;
};

template <typename T>
struct MyMonad {
    T value;
    MyMonad(T v) : value(v) {}

    template <typename F>
    auto flatMap(F&& f) -> decltype(f(value)) {
        return f(value);
    }
};
template <typename T>
MyMonad<T> unit(T a) {
    return MyMonad<T>(a);
}
static_assert(Monad<MyMonad, int>, "Not a monad");

auto to_string(int i) -> MyMonad<std::string> {
    return unit(std::to_string(i));
}

int main() {
    MyMonad<int> m(42);
    auto r = m.flatMap(to_string);
    std::cout << r.value << "\n";
    return 0;
}
