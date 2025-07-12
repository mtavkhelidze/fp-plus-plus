#ifndef FP_INTERNAL_STORAGE_STACK_H
#define FP_INTERNAL_STORAGE_STACK_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/tools/inner_type.h>
#include <fp/tools/rebind.h>

#include <type_traits>

namespace fp::internal::storage {

/**
 * Zero-overhead, stack-based storage for fundamental types (e.g., int, char).
 *
 * Used internally by functional containers via the `Object` selector.
 *
 * ## Constraints:
 * - Only fundamental types are supported (enforced via concept check).
 * - Instances must be created via the static `put()` method.
 * - Copying and moving are both allowed, since the value is trivially copyable.
 *
 * ## Access:
 * - Use `getOrElse(...)` to retrieve the value, though the fallback is ignored.
 * - No direct construction is allowed; intended for internal use only.
 *
 * ## Note:
 * Do not construct or manipulate this class unless you understand the internal
 * storage and trait system used by the library.
 */
template <class Container>
    requires std::is_fundamental_v<
      fp::tools::inner_type::fp_inner_type<Container>>
struct StorageStack {
  private:
    using A = fp::tools::inner_type::fp_inner_type<Container>;
    template <typename TC, typename T>
    using rebind = tools::rebind::fp_rebind<TC, T>;

    A value;

  protected:
    explicit StorageStack(A &&v) : value(v) {}

    StorageStack() = delete;
    StorageStack(const StorageStack &) noexcept = delete;
    StorageStack(StorageStack &&) noexcept = delete;
    StorageStack &operator=(const StorageStack &) noexcept = delete;
    StorageStack &operator=(StorageStack &&) noexcept = delete;

  protected:
    constexpr auto get() const noexcept -> const A & { return value; }

    constexpr auto empty() const noexcept -> bool { return false; }

    template <typename T>
    static auto put(T &&value) {
        using U = std::decay_t<T>;
        using Derived = rebind<Container, U>;
        return Derived{std::move(value)};
    }

#ifdef FP_PLUS_PLUS_TESTING
  protected:
    static constexpr const char *_tag = "StorageStack";
#endif
};
}  // namespace fp::internal::storage
#endif  // FP_INTERNAL_STORAGE_STACK_H
