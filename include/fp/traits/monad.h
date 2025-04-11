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
concept Misha = requires(M<A> m, A a) {
    {
        m.toBe(a)
    } -> std::same_as<
      typename std::invoke_result_t<decltype(&M<A>::toBe), M<A>, A>>;
};
}  // namespace fp::traits

#endif  // FP_TRAITS_MONAD_H
