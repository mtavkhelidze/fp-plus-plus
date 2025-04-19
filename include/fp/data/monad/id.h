#ifndef FP_DATA_MONAD_ID_H
#define FP_DATA_MONAD_ID_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/kernel/box.h>
#include <fp/tools.h>
#include <fp/traits/traits.h>

#include <type_traits>

namespace fp::data::monad::id {

using namespace fp::kernel::box;
using namespace fp::tools::all;
using namespace fp::traits::all;

using namespace fp::traits::applicative;

template <typename A>
struct Id {
  private:
    Box<A> box;

    // private:
    //   Id() = default;
    //   explicit Id(Box<A> value) : box(value) {}

    // public:
    //   Id(const Id&) = delete;
    //   Id(Id&&) = delete;

    //   template <typename T>
    //   static auto apply(T&& value) -> Id<std::decay_t<T>> {
    //       return Id(std::forward<std::decay_t<T>>(value));
    //   }

  public:
    explicit Id(Box<std::decay_t<A>>&& b) : box(std::move(b)) {}

    template <typename T>
    inline static auto apply(T&& a) -> Id<std::decay_t<T>> {
        return Id<std::decay_t<T>>{Box<T>{std::forward<std::decay_t<T>>(a)}};
    }

    // NOLINTNEXTLINE(google-explicit-constructor, hicpp-explicit-conversions)
    inline operator A() const { return *box.getOrNull(); }

    // Eq
    [[nodiscard]] auto equals(const Id& other) const -> bool {
        const auto a = *box.getOrNull();
        const auto b = *other.box.getOrNull();
        return a == b;
    }

    // Functor
    template <Arrow<A> F>
    [[nodiscard]] auto map(F&& f) const {
        auto v = *box.getOrNull();
        return pure<Id>(std::forward<F>(f)(v));
    }

    // // Monad
    // template <typename F>
    // auto flatMap(F&& f) const {
    //     return f(*value.getOrNull());  // f must return Id<U>
    // }
};

}  // namespace fp::data::monad::id

#ifdef FP_PLUS_PLUS_TESTING
namespace {
using namespace fp::data::monad::id;
using namespace fp::prelude;

static_assert(Eq<Id<int>>);
static_assert(Functor<Id<int>, identity_t>);
static_assert(Applicative<Id, int, int>);
}  // namespace

#endif  // FP_PLUS_PLUS_TESTING

#endif  // FP_DATA_MONAD_ID_H
