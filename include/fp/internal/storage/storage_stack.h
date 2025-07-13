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
 * - **Copying is allowed; moving is disallowed** to enforce strict copy
 * semantics.
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
    bool has_value = false;  // Tracks if a value has been stored

  public:
    // Default constructor: creates an empty StorageStack
    StorageStack() noexcept : has_value(false) {}

    // Destructor (defaulted)
    ~StorageStack() noexcept = default;

  protected:
    // Constructor for 'put()': takes rvalue, moves into 'value' (for semantic
    // correctness)
    explicit StorageStack(A &&v) noexcept
        : value(std::move(v)), has_value(true) {}

    // Copy constructor (defaulted): performs bitwise copy of A
    StorageStack(const StorageStack &) noexcept = default;

    // Copy assignment operator (defaulted): performs bitwise copy of A
    inline StorageStack &operator=(const StorageStack &) noexcept = default;

    // Explicitly delete move constructor and move assignment operator
    StorageStack(StorageStack &&) noexcept = delete;
    StorageStack &operator=(StorageStack &&) noexcept = delete;

  protected:
    // Accessor for the value
    constexpr auto get() const noexcept -> const A & {
        // Assert or handle if value is not present, though higher layers should
        // check empty() first
        return value;
    }

    // Checks if the StorageStack holds a value
    constexpr auto empty() const noexcept -> bool { return !this->has_value; }

    template <typename T>
    static auto put(T &&value) {
        using U = std::decay_t<T>;
        using Derived = rebind<Container, U>;
        // Calls StorageStack(A&& v) constructor, which moves 'value'
        return Derived{std::forward<T>(value)};
    }

#ifdef FP_PLUS_PLUS_TESTING
  protected:
    static constexpr const char *_tag = "StorageStack";
#endif
};
}  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_STACK_H
