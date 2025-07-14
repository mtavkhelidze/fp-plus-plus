#ifndef FP_INTERNAL_STORAGE_STACK_H
#define FP_INTERNAL_STORAGE_STACK_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/tools/inner_type.h>
#include <fp/internal/tools/rebind.h>

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
    StorageStack(const StorageStack &other) noexcept : value(other.value) {}
    inline StorageStack &operator=(const StorageStack &other) noexcept {
        value = other.value;
        return *this;
    }
    ~StorageStack() noexcept = default;

  private:
    explicit StorageStack(A &&v) noexcept : value(std::forward<A>(v)) {}

    StorageStack() noexcept = delete;
    StorageStack(StorageStack &&) noexcept = delete;
    StorageStack &operator=(StorageStack &&) noexcept = delete;

  protected:
    constexpr auto get() const noexcept -> const A & { return value; }

    template <typename T>
    static auto put(T &&value) {
        using U = std::decay_t<T>;
        using Derived = fp::tools::rebind::fp_rebind<Container, U>;
        return Derived{std::forward<T>(value)};
    }

#ifdef FP_PLUS_PLUS_TESTING
  protected:
    static constexpr const char *_tag = "StorageStack";
#endif
};
}  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_STACK_H
