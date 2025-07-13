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
 * - Values are stored as immutable `Box<A>` instances.
 * - The underlying `Box` manages data immutability via `shared_ptr<const A>`.
 * - **Copying is supported:** creates a new `StorageBox` instance that
 * shallow-copies its internal `Box` member, thus sharing the underlying
 * immutable value.
 * - **Moving is disallowed** to enforce stability and strict copy semantics.
 * - Access to the stored value is only via `const` methods returning
 * references.
 * - No mutation or non-const references are permitted.
 * - Low-level utility optimized for functional composition and immutability.
 */
template <class Container>
struct StorageBox {
  private:
    using A = fp::tools::inner_type::fp_inner_type<Container>;

    template <typename TC, typename T>
    using rebind = fp::tools::rebind::fp_rebind<TC, T>;

    using Box = fp::internal::box::Box<A>;  // Box is now copyable, not movable
    Box box;                                // Internal Box member

  public:
    StorageBox() noexcept : box() {}
    ~StorageBox() noexcept = default;

  protected:
    explicit StorageBox(const Box& b) noexcept : box(b) {}
    StorageBox(const StorageBox& other) noexcept = default;
    inline StorageBox& operator=(const StorageBox& other) noexcept = default;

    StorageBox(StorageBox&&) noexcept = delete;
    StorageBox& operator=(StorageBox&&) noexcept = delete;

  protected:
    inline constexpr auto get() const noexcept -> const A& { return box.get(); }

    inline constexpr auto empty() const noexcept -> bool { return box.empty(); }

    template <typename T>
    static auto put(T&& value) {
        // Create the Box. Box's constructor will handle the value.
        // The Box itself is not movable, so we can't std::move it here
        // if the Derived constructor takes an rvalue Box.
        // Instead, we pass it by const reference, triggering a copy of the Box.
        auto new_box = Box{std::forward<T>(value)};
        using U = typename decltype(new_box)::kind;
        using Derived = rebind<Container, U>;
        return Derived{
          new_box
        };  // Pass by const ref, which calls StorageBox(const Box& b)
    }

#ifdef FP_PLUS_PLUS_TESTING
  protected:
    static constexpr const char* _tag = "StorageBox";
#endif
};

}  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_BOX_H
