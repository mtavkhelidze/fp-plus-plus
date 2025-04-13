#include <fp/fp.h>

#include <iostream>
#include <string>

using namespace fp::traits::monad;

template <typename T>
struct Id {
    const T box;

    auto toString() const -> std::string { return std::string(box); }

    template <fp_kleisli_arrow<T, Id> F>
    auto flatMap(F&& f) const -> std::invoke_result_t<F, T> {
        return std::forward<F>(f)(box);
    };
};
static_assert(Monad<Id, int>);

int main() {
    auto stringify = [](int x) -> const Id<std::string> {
        return pure<Id>(std::to_string(x));
    };
    Id<int> id{42};
    auto result = id.flatMap(stringify);
    std::cout << "Result: " << result.toString() << "\n";
    return 0;
}
