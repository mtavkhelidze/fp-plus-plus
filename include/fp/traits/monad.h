#include <functional>
#include <type_traits>
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_MONAD_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_MONAD_H

#include <concepts>

namespace fp::traits {
template <template <typename> typename M, typename A>
concept HasApply = requires(A a) {
    { M<A>(a) };
};

template <template <typename> typename M, typename A>
concept HasUnit = HasApply<M, A> && requires(A a) {
    { unit(a) } -> std::same_as<M<A>>;
};

template <template <typename> typename M, typename A, typename B = A>
concept HasFlatMap = HasUnit<M, A> && requires(M<A> m) {
    {
        m.flatMap([](A a) -> M<B> { return unit<M>(a); })
    } -> std::same_as<M<B>>;
};

template <typename F, typename A, typename B>
concept Unary = requires(F f, A a) {
    { f(a) } -> std::same_as<std::decay_t<B>>;
};

template <template <typename> typename M, typename A, typename B = A>
concept Monad = HasUnit<M, A> && HasFlatMap<M, A, B>;

template <template <typename> typename M, typename A>
    requires HasApply<M, std::decay_t<A>>
auto unit(A&& a) -> M<A> {
    return M(std::forward<A>(a));
}
}  // namespace fp::traits

#endif  // FP_TRAITS_MONAD_H
