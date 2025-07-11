#ifndef FP_CORE_ID_H
#define FP_CORE_ID_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/types.h>
#include <fp/mixins/value.h>
#include <fp/prelude/pure.h>

#include <utility>

namespace fp::core {

template <typename A>
struct Id : fp::mixins::value::WithValue<Id<A>> {
  private:
    using Base = fp::mixins::value::WithValue<Id>;
    using Base::Base;

  public:
    template <typename Fn>
    auto map(Fn&& f) const {
        return fp::core::types::Functor<Id>::map(*this, std::forward<Fn>(f));
    }
};

}  // namespace fp::core

namespace fp::core::types {
template <typename A>
struct Functor<Id<A>> {
    template <
      __::Arrow<A> Fn,
      typename B = __::fp_arrow_result<Fn, A>,
      typename F>
    [[nodiscard]]
    static constexpr auto map(F&& fa, Fn&& f) noexcept(
      noexcept(f(std::forward<F>(fa).value()))
    ) -> Id<B> {
        return fp::prelude::pure<Id>(f(std::forward<F>(fa).value()));
    }
};
}  // namespace fp::core::types

#endif  // FP_CORE_ID_H
