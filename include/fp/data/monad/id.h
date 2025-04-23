#ifndef FP_DATA_MONAD_ID_H
#define FP_DATA_MONAD_ID_H

#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage.h>
#include <fp/prelude.h>
#include <fp/tools.h>

namespace fp::data::monad::id {

template <typename A>
using Storage = fp::internal::storage::Storage<A>;

using namespace fp::tools::arrow;

template <typename A>
struct Id : public Storage<A> {
    inline operator A() const { return this->getOrElse(A{}); }

    template <typename T>
    static auto apply(T&& value) -> Id<std::decay_t<T>> {
        return Id{Storage<std::decay_t<T>>::store(std::forward<T>(value))};
    }

    // Eq
    [[nodiscard]] auto equals(const Id& other) const -> bool {
        const auto a = this->getOrElse(A{});
        const auto b = other.getOrElse(A{});
        return a == b;
    }

    // Functor
    template <Arrow<A> F>
    [[nodiscard]] auto map(F&& f) const {
        auto v = this->getOrElse(A{});
        return Id<A>::apply(std::forward<F>(f)(v));
    }
};

}  // namespace fp::data::monad::id

#ifdef FP_PLUS_PLUS_TESTING
#include <fp/traits/traits.h>
namespace {
using namespace fp::data::monad::id;
using namespace fp::prelude;
using namespace fp::tools::all;
using namespace fp::traits::all;

static_assert(Eq<Id<int>>);
static_assert(Functor<Id<int>, identity_t>);
static_assert(Applicative<Id, int, int>);
}  // namespace

#endif  // FP_PLUS_PLUS_TESTING

#endif  // FP_DATA_MONAD_ID_H
