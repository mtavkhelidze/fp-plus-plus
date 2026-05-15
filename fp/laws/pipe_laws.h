#ifndef __FP_LAWS_PIPE_LAWS_H
#define __FP_LAWS_PIPE_LAWS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif

#include <fp/data/data.h>
#include <fp/kernel/ops/ops.h>

#include <utility>

namespace fp::laws {

struct PipeLaws {
    // Law 1: left identity — id | f == f
    template <typename Fn, typename A>
    static auto left_identity(Fn&& f, A&& a) -> bool {
        return fp::kernel::ops::
                 pipe(fp::kernel::ops::identity, std::forward<Fn>(f))(
                   std::forward<A>(a)
                 )
            == std::forward<Fn>(f)(std::forward<A>(a));
    }

    // Law 2: right identity — f | id == f
    template <typename Fn, typename A>
    static auto right_identity(Fn&& f, A&& a) -> bool {
        return fp::kernel::ops::
                 pipe(std::forward<Fn>(f), fp::kernel::ops::identity)(
                   std::forward<A>(a)
                 )
            == std::forward<Fn>(f)(std::forward<A>(a));
    }

    // Law 3: associativity — (f | g) | h == f | (g | h)
    template <typename F, typename G, typename H, typename A>
    static auto associativity(F&& f, G&& g, H&& h, A&& a) -> bool {
        auto lhs = fp::kernel::ops::pipe(
          fp::kernel::ops::pipe(std::forward<F>(f), std::forward<G>(g)),
          std::forward<H>(h)
        );
        auto rhs = fp::kernel::ops::pipe(
          std::forward<F>(f),
          fp::kernel::ops::pipe(std::forward<G>(g), std::forward<H>(h))
        );
        return lhs(std::forward<A>(a)) == rhs(std::forward<A>(a));
    }

    // Law 4: variadic consistency — pipe(f,g,h)(a) == h(g(f(a)))
    template <typename F, typename G, typename H, typename A>
    static auto variadic(F&& f, G&& g, H&& h, A&& a) -> bool {
        auto v = fp::kernel::ops::pipe(
          std::forward<F>(f), std::forward<G>(g), std::forward<H>(h)
        );
        auto expected = std::forward<H>(h)(
          std::forward<G>(g)(std::forward<F>(f)(std::forward<A>(a)))
        );
        return v(std::forward<A>(a)) == expected;
    }
};

}  // namespace fp::laws

#endif  // __FP_LAWS_PIPE_LAWS_H
