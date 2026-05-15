#ifndef __FP_LAWS_APPLICATIVE_LAWS_H
#define __FP_LAWS_APPLICATIVE_LAWS_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  //  FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/meta.h>
#include <fp/kernel/ops/ops.h>
#include <fp/kernel/traits/traits.h>

namespace fp::laws {

template <template <typename> typename F>
    requires kernel::traits::IsApplicative<F>
struct ApplicativeLaws {
    // Law 1: Identity — ap(pure(identity), fa) == fa
    template <typename A>
    static auto identity(const F<A>& fa) -> bool {
        auto ff = kernel::ops::pure<F>(kernel::ops::identity);
        return core::Applicative<F>::ap(ff)(fa).value() == fa.value();
    }

    // Law 2: Homomorphism — ap(pure(f), pure(a)) == pure(f(a))
    template <typename Fn, typename A>
        requires internal::meta::arrow::is_arrow<Fn, A>
    static auto homomorphism(Fn&& f, const A& a) -> bool {
        auto ff = kernel::ops::pure<F>(f);
        auto fa = kernel::ops::pure<F>(a);
        return core::Applicative<F>::ap(ff)(fa).value()
            == kernel::ops::pure<F>(f(a)).value();
    }

    // Law 3: Interchange — ap(ff, pure(a)) == ap(pure(f => f(a)), ff)
    template <typename Fn, typename A>
        requires internal::meta::arrow::is_arrow<Fn, A>
    static auto interchange(const F<Fn>& ff, const A& a) -> bool {
        auto fa = kernel::ops::pure<F>(a);
        auto lhs = core::Applicative<F>::ap(ff)(fa).value();
        auto applyA = [a](const Fn& f) -> auto { return f(a); };
        auto rhs =
          core::Applicative<F>::ap(kernel::ops::pure<F>(applyA))(ff).value();
        return lhs == rhs;
    }

    // Law 4: Composition — ap(ap(ap(pure(compose), ff), fg), fa) == ap(ff,
    // ap(fg, fa))
    template <typename Fn, typename Gn, typename A>
        requires internal::meta::arrow::is_arrow<Gn, A>
              && internal::meta::arrow::
                   is_arrow<Fn, internal::meta::arrow::arrow_result<Gn, A>>
    static auto composition(const F<Fn>& ff, const F<Gn>& fg, const F<A>& fa)
      -> bool {
        auto composeFn = [](const Fn& f) {
            return [f](const Gn& g) { return kernel::ops::compose(f, g); };
        };
        auto lhs =
          core::Applicative<F>::
            ap(core::Applicative<F>::ap(core::Applicative<F>::ap(kernel::ops::pure<F>(composeFn))(ff))(fg))(
              fa
            )
              .value();
        auto rhs =
          core::Applicative<F>::ap(ff)(core::Applicative<F>::ap(fg)(fa))
            .value();
        return lhs == rhs;
    }
};

}  // namespace fp::laws
#endif  // __FP_LAWS_APPLICATIVE_LAWS_H
