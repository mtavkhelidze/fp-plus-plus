#ifndef FP_INTERNAL_STACK_STORAGE_H
#define FP_INTERNAL_STACK_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <type_traits>
#include <utility>

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
 * - StackStorage instances can only be created via the static `store()` method.
 * - Copying and moving are both allowed as the underlying value is trivially
 *   copyable.
 * - - Values are accessed via `getOrElse(alternative)`, though the alternative
 * is never used. (see @ref{fp::internal::storage::BoxStorage} for different
 * case)
 *
 * Do not construct or manipulate this unless you know what you're doing.
 */
template <template <typename> typename Master, typename A>
    requires std::is_fundamental_v<A>
struct StackStorage {
  private:
    A value;

  protected:
    explicit StackStorage(A v) : value(v) {}
    StackStorage(const StackStorage&) noexcept = default;
    StackStorage(StackStorage&&) noexcept = delete;
    StackStorage& operator=(const StackStorage&) noexcept = delete;
    StackStorage& operator=(StackStorage&&) noexcept = default;

    template <typename T>
    static auto store(T&& x) -> Master<std::decay_t<T>> {
        return Master<std::decay_t<T>>(std::forward<std::decay_t<T>>(x));
    }

  public:
    auto getOrElse(const A&) const -> A { return value; }

#ifdef FP_PLUS_PLUS_TESTING
  public:
    static constexpr const char* _backend_tag() { return "StackStorage"; }
    constexpr const char* backend_tag() const { return _backend_tag(); }
#endif
};
}  // namespace fp::internal::storage
#endif  // FP_INTERNAL_STACK_STORAGE_H
