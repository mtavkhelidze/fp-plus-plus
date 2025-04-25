#ifndef FP_INTERNAL_BOX_STORAGE_H
#define FP_INTERNAL_BOX_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/box.h>
#include <fp/tools.h>

namespace fp::internal::storage {
/**
 * Internal boxed value storage abstraction.
 *
 * This class provides a uniform behavior layer for storing values inside a Box.
 * It is not intended for direct use. Instead, it is designed to be inherited
 * by functional containers like @ref{fp::internal::storage::StorageProvider}
 * using CRTP.
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
template <template <typename> class Container, typename A>
struct StorageBox {
  private:
    template <typename TC, typename T>
    using rebind = fp::tools::rebind::fp_rebind<TC, T>;

    using Box = fp::internal::box::Box<A>;
    Box box;

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
        using Derived = rebind<Container<A>, U>;
        return Derived{std::move(box)};
    }

#ifdef FP_PLUS_PLUS_TESTING
  protected:
    static constexpr const char* _tag = "StorageBox";
#endif
};

#endif  // FP_INTERNAL_BOX_STORAGE_H
}  // namespace fp::internal::storage
