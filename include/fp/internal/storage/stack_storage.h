#ifndef FP_INTERNAL_STORAGE_STACK_STORAGE_H
#define FP_INTERNAL_STORAGE_STACK_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/inner_type.h>
#include <fp/tools/rebind.h>

#include <type_traits>

namespace fp::internal::storage {

/**
 * Copy-only, always-initialized storage for fundamental types only.
 *
 * No move operations allowed.
 * Construction requires a value; no empty state is possible.
 */
template <class Container>
    requires std::is_fundamental_v<
      fp::tools::inner_type::fp_inner_type<Container>>
struct StorageStack {
  private:
    using A = fp::tools::inner_type::fp_inner_type<Container>;
    A value;

  protected:
    StorageStack(const StorageStack& other) noexcept : value(other.value) {}
    auto operator=(const StorageStack& other) noexcept
      -> StorageStack& = default;
    ~StorageStack() noexcept = default;

  private:
    explicit StorageStack(A&& /* NOLINT */ v) noexcept
        : value(std::forward<A>(v)) {}

  public:
    StorageStack() noexcept = delete;
    StorageStack(StorageStack&&) noexcept = delete;
    auto operator=(StorageStack&&) noexcept -> StorageStack& = delete;

  protected:
    constexpr auto get() const noexcept -> const A& { return value; }

    /**
     * Constructs the derived container from a raw C++ type `T`.
     *
     * Here, `T` is the raw C++ type used as input,
     * and `U` is the normalized FP type (decayed `T`).
     * The function returns an instance of the derived container,
     * i.e., `fp_rebind<Container, U>`.
     */
    template <typename T>
    static auto put(T&& value) {
        using U = std::decay_t<T>;
        using Derived = fp::tools::rebind::fp_rebind<Container, U>;
        return Derived{std::forward<T>(value)};
    }

#ifdef FP_PLUS_PLUS_TESTING
    static constexpr const char* _tag = "StorageStack";
#endif
};
}  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_STACK_STORAGE_H
