#ifndef FP_INTERNAL_STACK_STORAGE_H
#define FP_INTERNAL_STACK_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/rebind.h>

#include <type_traits>

namespace fp::internal::storage {

/**
 * Internal stack-based, zero-overhead storage abstraction for values of
 * fundamental types (i.e.int, char).
 *
 * This struct is not intended for direct construction — values must be created
 * via the static `store()` method. The struct must be used by `Master`
 * container via @ref{StorageProvider} selector template.
 *
 * ## Constraints:
 * - StorageStack
 *  instances can only be created via the static `store()` method.
 * - Copying and moving are both allowed as the underlying value is trivially
 *   copyable.
 * - - Values are accessed via `getOrElse(alternative)`, though the alternative
 * is never used. (see @ref{fp::internal::storage::StorageBox} for different
 * case)
 *
 * Do not construct or manipulate this unless you know what you're doing.
 */
template <template <typename> class Container, typename A>
    requires std::is_fundamental_v<A>
struct StorageStack {
  private:
    template <typename TC, typename T>
    using rebind = fp::tools::rebind::fp_rebind<TC, T>;

    A value;

  private:
    explicit StorageStack(A &&v) : value(v) {}

    StorageStack() = delete;
    StorageStack(const StorageStack &) noexcept = default;
    StorageStack(StorageStack &&) noexcept = delete;
    StorageStack &operator=(const StorageStack &) noexcept = delete;
    StorageStack &operator=(StorageStack &&) noexcept = default;

  protected:
    constexpr auto get() const noexcept -> const A & { return value; }

    inline constexpr auto empty() const noexcept -> bool { return false; }
    template <typename T>
    static auto put(T &&value) {
        using U = std::decay_t<T>;
        using Derived = rebind<Container<A>, U>;
        return Derived{std::move(value)};
    }

#ifdef FP_PLUS_PLUS_TESTING
  protected:
    static constexpr const char *_tag = "StorageStack";
#endif
};
}  // namespace fp::internal::storage
#endif  // FP_INTERNAL_STACK_STORAGE_H
