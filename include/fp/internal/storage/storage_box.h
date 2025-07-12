#ifndef FP_INTERNAL_STORAGE_BOX_H
#define FP_INTERNAL_STORAGE_BOX_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/box.h>
#include <fp/tools/all.h>

namespace fp::internal::storage {
/**
 * Internal boxed value storage abstraction (`StorageBox`).
 *
 * This class provides a uniform interface for value storage within `Box`,
 * intended for use via CRTP in functional containers (e.g.,
 * `fp::internal::storage::Object`).
 *
 * ## Constraints:
 * - Instances must be created via the static `put()` method.
 * - Values are stored as move-only `Box<A>` instances.
 * - Deep copying is allowed (if the value supports it); moving transfers
 * ownership.
 *
 * ## Access:
 * - Values are only accessible via `getOrElse(const A&)` or `get()`.
 * - No direct mutation or reference access is allowed after construction.
 *
 * ## Note:
 * This is a low-level utility with a restricted API, optimized for functional
 * composition. It should not be constructed or used directly.
 */
template <class Container>
struct StorageBox {
  private:
    using A = fp::tools::inner_type::fp_inner_type<Container>;

    template <typename TC, typename T>
    using rebind = fp::tools::rebind::fp_rebind<TC, T>;

    using Box = fp::internal::box::Box<A>;
    Box box;

  protected:
    explicit StorageBox(Box&& box) noexcept : box(std::move(box)) {}

    StorageBox() noexcept = delete;
    StorageBox(const StorageBox& other) noexcept = delete;
    StorageBox(StorageBox&& other) noexcept = delete;
    StorageBox& operator=(const StorageBox&) noexcept = delete;
    StorageBox& operator=(StorageBox&&) noexcept = delete;

  protected:
    constexpr auto get() const noexcept -> const A& { return box.get(); }

    inline constexpr auto empty() const noexcept -> bool { return box.empty(); }

    template <typename T>
    static auto put(T&& value) {
        auto box = Box{std::forward<T>(value)};
        using U = typename decltype(box)::kind;
        using Derived = rebind<Container, U>;
        return Derived{std::move(box)};
    }

#ifdef FP_PLUS_PLUS_TESTING
  protected:
    static constexpr const char* _tag = "StorageBox";
#endif
};

#endif  // FP_INTERNAL_STORAGE_BOX_H
}  // namespace fp::internal::storage
