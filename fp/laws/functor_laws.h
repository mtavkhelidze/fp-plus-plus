#ifndef __FP_LAWS_FUNCTOR_LAWS_H
#define __FP_LAWS_FUNCTOR_LAWS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/data.h>
#include <fp/kernel/ops/ops.h>
#include <fp/kernel/traits/traits.h>

namespace fp::laws {
// fp/laws/functor.h
template <template <typename> typename F>
    requires kernel::traits::IsFunctor<F>
struct FunctorLaws {
    static auto identity(const F<int>& fa) -> bool {
        return kernel::ops::fmap(kernel::ops::id)(fa).value() == fa.value();
    }

    static auto composition(const F<int>& fa) -> bool {
        auto f = [](int x) -> auto { return x * 2; };
        auto g = [](int x) -> auto { return x + 3; };
        return kernel::ops::fmap(g)(fmap(f)(fa)).value()
            == kernel::ops::fmap([&](int x) -> auto { return g(f(x)); })(fa)
                 .value();
    }
};
}  // namespace fp::laws

#endif  // __FP_LAWS_FUNCTOR_LAWS_H
