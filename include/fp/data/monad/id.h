#ifndef FP_DATA_MONAD_ID_H
#define FP_DATA_MONAD_ID_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/storage_provider.h>
#include <fp/prelude.h>
#include <fp/tools.h>

namespace fp::data::monad::id {

template <template <typename> typename TC, typename A>
using StorageProvider = fp::internal::storage::StorageProvider<TC, A>;

using namespace fp::tools::arrow;

template <typename A>
struct Id : public StorageProvider<Id, A> {
  private:
    using Base = StorageProvider<Id, A>;
    using Base::Base;

  public:
    inline constexpr operator A() const noexcept { return this->value(); }

    template <typename T>
    inline static constexpr auto apply(
      T&& value
    ) noexcept(std::is_nothrow_constructible_v<A, T&&>) -> Id {
        return Id{Id::store(std::forward<T>(value))};
    }

    inline constexpr auto value() const noexcept -> const A& {
        return this->retrieve();
    }

    // Eq
    // [[nodiscard]] auto equals(const Id& other) const -> bool {
    //     const auto a = this->get();
    //     const auto b = other.get();
    //     return a == b;
    // }

    // // Functor
    // template <Arrow<A> F>
    // [[nodiscard]] auto map(F&& f) const {
    //     if (!this->empty()) {
    //         auto v = this->get();
    //         return this->apply(std::forward<F>(f)(v));
    //     }
    //     return this->apply(this->get());
    // }
};

}  // namespace fp::data::monad::id

// #ifdef FP_PLUS_PLUS_TESTING
// #include <fp/traits/traits.h>
// namespace {
// using namespace fp::data::monad::id;
// using namespace fp::prelude;
// using namespace fp::tools::all;
// using namespace fp::traits::all;

// static_assert(Eq<Id<int>>);
// static_assert(Functor<Id<int>, identity_t>);
// static_assert(Applicative<Id, int, int>);
// }  // namespace

// #endif  // FP_PLUS_PLUS_TESTING

#endif  // FP_DATA_MONAD_ID_H
