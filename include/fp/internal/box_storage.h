#ifndef FP_INTERNAL_BOX_STORAGE_H
#define FP_INTERNAL_BOX_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/box.h>

#include <iostream>

namespace fp::internal::storage::box {
/**
 * Internal boxed value storage abstraction.
 *
 * This class provides a uniform behavior layer for storing values inside a Box.
 * It is not intended for direct use. Instead, it is designed to be inherited
 * by functional containers like @ref{fp::internal::storage::Storage} using
 * CRTP.
 *
 * ## Constraints:
 * - BoxedStorage instances can only be created via the static `store()` method.
 * - Underlying value is always stored as a move-only `Box<A>`.
 * - Copying is allowed: performs a deep copy of the stored value (if any).
 * - Moving transfers ownership of the Box.
 *
 * ## Access:
 * - Values can only be accessed via `getOrElse(const A&)`, which safely returns
 *   the stored value if present or the fallback alternative.
 * - No reference access or mutation is allowed post-construction.
 *
 * ## Note:
 * Do not construct or manipulate this class directly. It is a low-level utility
 * with intentionally restricted interface, optimized for functional semantics.
 */
template <template <typename> typename TC, typename A>
struct BoxedStorage {
    template <typename T>
    using Derived = fp::tools::rebind::fp_rebind<TC<A>, T>;
    using Box = fp::internal::box::Box<A>;

  private:
    Box box;

  protected:
    // 1. Default constructor
    explicit BoxedStorage() : box() {}

    // 2. Constructor from value
    explicit BoxedStorage(const A& value) : box(value) {}

    // 3. Copy constructor
    BoxedStorage(const BoxedStorage& other)
        : box([&]() {
            auto* ptr = other.box.getOrNull();
            return ptr ? Box(*ptr) : Box();
        }()) {}

    // 4. Move constructor
    BoxedStorage(BoxedStorage&& other) noexcept : box(std::move(other.box)) {}

  public:
    template <typename T>
    static auto store(T&& value) -> Derived<std::decay_t<T>> {  //
        return Derived<std::decay_t<T>>{std::forward<T>(value)};
    }

    auto getOrElse(const A& alt) const -> A {
#ifdef FP_PLUS_PLUS_TESTING
        if (auto* ptr = box.getOrNull()) {
            std::cout << "Boxed value: " << *ptr << std::endl;
        }
#endif
        auto* ptr = box.getOrNull();
        return ptr == nullptr ? alt : *ptr;
    }
};

#endif  // FP_INTERNAL_BOX_STORAGE_H
}
