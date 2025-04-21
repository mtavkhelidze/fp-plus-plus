
#ifndef FP_INTERNAL_STORAGE_H

#define FP_INTERNAL_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/box_storage.h>
#include <fp/internal/stack_storage.h>

namespace fp::internal::storage {
template <template <typename> typename TC, typename A>
using __box_storage = fp::internal::storage::box::BoxedStorage<TC, A>;

template <template <typename> typename TC, typename A>
using __stack__storage = fp::internal::storage::stack::StackStorage<TC, A>;

template <template <typename> typename TC, typename A>
struct StorageProvider {
    using type = __box_storage<TC, A>;
};

template <template <typename> typename TC, typename A>
    requires(std::is_fundamental_v<A>)
struct StorageProvider<TC, A> {
    using type = __stack__storage<TC, A>;
};

/**
 * A generic storage container for values.
 *
 * This class provides a unified interface for different storage strategies
 * based on the type of the value. It selects between heap-based storage
 * (BoxedStorage) for non-fundamental types, and stack-based storage
 * (StackStorage) for fundamental types.
 *
 * ## Usage:
 * - The appropriate storage strategy is automatically chosen based on the type
 *   of the value.
 * - The storage mechanism is selected via `StorageSelector`, which evaluates
 *   whether the type is fundamental or not, and chooses `StackStorage` or
 *   `BoxedStorage` accordingly.
 * - This class **does not directly store the value**; instead, it delegates the
 *   storage responsibility to either `BoxedStorage` or `StackStorage` depending
 *   on the type.
 *
 * ## Constraints:
 * - Storage is automatically chosen based on the type of `T`, and users do not
 *   need to manually select a storage strategy.
 * - Values are accessible via the storage strategy's `getOrElse()` method.
 */
template <typename T>
struct Storage : public StorageProvider<Storage, std::decay_t<T>>::type {
  private:
    using SP = typename StorageProvider<Storage, std::decay_t<T>>::type;
    friend SP;

  public:
    using SP::SP;
};

};  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_H
