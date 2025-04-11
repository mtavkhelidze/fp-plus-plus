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
template <template <typename> typename M, typename A, typename B = A>
concept Monad = requires(M<A> m, A a, std::function<M<B>(A)> f) {
    requires std::constructible_from<M<A>, A>;
    // requires std::same_as<std::decay_t<decltype(unit(a))>, M<A>>;
    requires std::same_as<
      std::decay_t<decltype(m.template flatMap<B>(f))>, M<B>>;
};

template <template <typename> typename M, typename A>
    requires Monad<M, A>
auto unit(A&& a) -> M<std::decay_t<A>> {
    return M<std::decay_t<A>>(std::forward<A>(a));
}

}  // namespace fp::traits

#endif  // FP_TRAITS_MONAD_H
