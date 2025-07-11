#ifndef FP_DATA_MONAD_ID_H
#define FP_DATA_MONAD_ID_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/mixins/value.h>
#include <fp/prelude/pure.h>
#include <fp/types/all.h>

#include <utility>

namespace fp::data::id {

template <typename A>
struct Id : fp::mixins::value::WithValue<Id<A>> {
  private:
    using Base = fp::mixins::value::WithValue<Id>;
    using Base::Base;

  public:
    template <typename Fn>
    auto map(Fn&& f) const {
        return fp::types::Functor<Id>::map(*this, std::forward<Fn>(f));
    }
};

}  // namespace fp::data::id

namespace fp::types {
template <typename A>
struct Functor<fp::data::id::Id<A>> {
    template <
      __::Arrow<A> Fn,
      typename B = __::fp_arrow_result<Fn, A>,
      typename F>
    [[nodiscard]]
    static constexpr auto map(F&& fa, Fn&& f) noexcept(
      noexcept(f(std::forward<F>(fa).value()))
    ) -> fp::data::id::Id<B> {
        return fp::prelude::pure<fp::data::id::Id>(
          f(std::forward<F>(fa).value())
        );
    }
};
}  // namespace fp::types

#endif  // FP_DATA_MONAD_ID_H
