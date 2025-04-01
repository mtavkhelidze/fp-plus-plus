#ifndef __FP_PP_SYNTAX_H__
#define __FP_PP_SYNTAX_H__

#ifndef __FP_PLUS_PLUS__
#error "This file must be included from fp/fp"
#endif

#include <concepts>
#include <functional>

namespace fp {

template <typename A>
constexpr auto operator<<(A a, std::invocable<A> auto f) {
    return f(a);
}
template <typename F, typename G>
    requires std::invocable<F, typename std::invoke_result_t<G>::type>
auto operator<<(F&& lhs, G&& rhs) {
    return [lhs = std::forward<F>(lhs), rhs = std::forward<G>(rhs)](auto a) {
        return rhs(lhs(a));
    };
}
}  // namespace fp
#endif  // __FP_PP_SYNTAX_H__
