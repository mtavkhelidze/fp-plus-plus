#include <concepts>
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>

namespace monad {
template <typename F, template <typename> typename M, typename A, typename B>
concept FlatMapUnary =
  std::invocable<F, A> && !std::is_reference_v<B> &&
  std::same_as<std::invoke_result_t<F, A>, M<std::decay_t<B>>>;

template <template <typename> typename M, typename A>
concept HasApply = std::is_nothrow_constructible_v<M<A>, A>;

template <template <typename> typename M, typename A>
concept HasUnit = HasApply<M, A> && requires(A a) {
    { M<A>::unit(a) } -> std::convertible_to<M<std::decay_t<A>>>;
};

template <template <typename> typename M, typename F, typename A, typename B>
concept HasFlatMap = HasUnit<M, A> && requires(M<A> m, F f) {
    FlatMapUnary<F, M, A, B>;
    { m.flatMap(f) } -> std::same_as<M<std::decay_t<B>>>;
};

template <
  template <typename> typename M, typename F, typename A, typename B = A>
concept Monad = HasApply<M, A> && HasUnit<M, A> && HasFlatMap<M, F, A, B>;

}  // namespace monad

using namespace monad;

template <typename T>
struct Simple {
    T value;
    static auto unit(T a) -> const Simple<T> { return Simple{a}; }

    auto flatMap(auto&& f) const
      -> Simple<std::decay_t<decltype(f(value).value)>> {
        return std::forward<decltype(f)>(f)(value);
    }
};
template <typename A, typename B = A>
using Fn = std::function<Simple<B>(A)>;

static_assert(monad::Monad<Simple, Fn<int, int>, int>);

auto stringify(int x) -> const Simple<std::string> {
    return Simple<std::string>::unit(std::to_string(x));
}

auto twice(int x) -> const Simple<int> { return Simple<int>::unit(x * 2); };

auto addSuffix = [](auto suf) {
    return [suf](auto x) { return Simple<std::string>::unit(x + suf); };
};

auto addSir = addSuffix(", Sir!");

int main() {
    const int x = 21;
    Simple<int> s = Simple<int>::unit(x);
    auto result = s.flatMap(twice)
                    .flatMap(stringify)
                    .flatMap(addSuffix(" is the right number"))
                    .flatMap(addSir);

    std::cout << x << ": " << result.value
              << std::endl;  // should print 42    return 0;
    return 0;
}
