#include <fp/fp.h>

#include <iostream>
#include <string>

using namespace fp::traits::monad;
using namespace fp::syntax;

template <typename T>
struct Id {
    const T box;

    auto toString() const -> std::string {
        if constexpr (std::is_same_v<T, std::string>) {
            return box;
        } else {
            return std::to_string(box);
        };
    }

    template <fp_kleisli_arrow<T, Id> F>
    auto flatMap(F &&f) const -> std::invoke_result_t<F, T> {
        return std::forward<F>(f)(box);
    };
};

int main() {
    auto addOne = [](int x) -> const Id<int> { return pure<Id>(x + 1); };
    auto stringify = [](int x) -> const Id<std::string> {
        return pure<Id>(std::to_string(x));
    };
    auto triple = [](int x) -> int { return x * 3; };

    auto monadChain = liftM<Id>(triple) >>= addOne >>= stringify;
    std::cout << "Result: " << monadChain(52).toString() << "\n";
    return 0;
}
