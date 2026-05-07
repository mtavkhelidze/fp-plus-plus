#ifndef FP_INTERNAL_STORAGE_STACK_STORAGE_H
#define FP_INTERNAL_STORAGE_STACK_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/meta/inner_type.h>
#include <fp/internal/meta/rebind.h>

namespace fp::internal::storage {

/**
 * Copy-only, always-initialized storage for fundamental types only.
 *
 * No move operations allowed.
 * Construction requires a value; no empty state is possible.
 */
template <class Container>
    requires std::is_fundamental_v<meta::inner_type::inner_type<Container>>
struct StorageStack {
  private:
    using A = meta::inner_type::inner_type<Container>;
    A value;

  protected:
    constexpr StorageStack(const StorageStack& other) noexcept
        : value(other.value) {}
    constexpr auto operator=(const StorageStack& other) noexcept
      -> StorageStack& = default;
    constexpr ~StorageStack() noexcept = default;

  private:
    constexpr explicit StorageStack(A&& v) noexcept : value(v) {}

  protected:
    explicit StorageStack() noexcept = delete;
    explicit StorageStack(StorageStack&&) noexcept = delete;
    auto operator=(StorageStack&&) noexcept -> StorageStack& = delete;

  protected:
    constexpr auto get() const noexcept -> const A& { return value; }

    /**
     * Constructs the derived container from a raw C++ type `T`.
     *
     * Here, `T` is the raw C++ type used as input,
     * and `U` is the normalized FP type (decayed `T`).
     * The function returns an instance of the derived container,
     * i.e., `rebind<Container, U>`.
     */
    template <typename T>
    static auto put(T&& value) noexcept {
        using U = std::decay_t<T>;
        using Derived = meta::rebind::rebind<Container, U>;
        return Derived{std::forward<T>(value)};
    }

#ifdef FP_PLUS_PLUS_TESTING
    static constexpr const char* _tag = "StorageStack";
#endif
};
}  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_STACK_STORAGE_H
