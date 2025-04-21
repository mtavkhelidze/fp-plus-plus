#ifndef FP_DATA_MONAD_ID_H
#define FP_DATA_MONAD_ID_H
#include <ratio>
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage.h>

namespace fp::data::monad::id {

template <typename A>
using Storage = fp::internal::storage::Storage<A>;

template <typename A>
struct Id : public Storage<A> {
    template <typename T>
    static auto apply(T&& value) -> Id<std::decay_t<T>> {
        return Id{Storage<T>::store(std::forward<std::decay_t<T>>(value))};
    }

    // Eq
    [[nodiscard]] auto equals(const Id& other) const -> bool {
        const auto a = this->getOrElse(A{});
        const auto b = other.getOrElse(A{});
        return a == b;
    }
};

}  // namespace fp::data::monad::id

#endif  // FP_DATA_MONAD_ID_H
