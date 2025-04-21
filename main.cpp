#include <fp/fp.h>

#include <iostream>
#include <type_traits>
#include <utility>

namespace func {
using namespace fp::tools::instance;

template <template <typename> typename FA, typename A>
    requires(UnaryInstance<FA<A>>)
constexpr auto pure(A&& a) -> FA<std::decay_t<A>> {
    return FA<std::decay_t<A>>::apply(std::forward<A>(a));
}
}  // namespace func

auto main() -> int {
    int fortyTwo = 42;
    auto id = fp::data::monad::id::Id<int>::apply(fortyTwo);
    std::cout << id.getOrElse(0) << std::endl;
    return 0;
}
