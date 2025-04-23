
#ifndef FP_INTERNAL_STORAGE_H

#define FP_INTERNAL_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/box_storage.h>
#include <fp/internal/stack_storage.h>

namespace fp::internal::storage {

/// Canonical storage type: normalize const char* and char* to std::string, else
/// decay
template <typename T>
struct canonical_storage_type {
    using type = std::conditional_t<
      std::is_same_v<std::decay_t<T>, const char*>
        || std::is_same_v<std::decay_t<T>, char*>,
      std::string,
      std::decay_t<T>>;
};

template <typename T>
using __canonical_storage_t = typename canonical_storage_type<T>::type;

template <template <typename> typename TC, typename A>
using __box_storage = fp::internal::storage::box::BoxedStorage<TC, A>;

template <template <typename> typename TC, typename A>
using __stack__storage = fp::internal::storage::stack::StackStorage<TC, A>;

template <template <typename> typename TC, typename A>
struct StorageProvider {
    using type = __box_storage<TC, __canonical_storage_t<A>>;
};

template <template <typename> typename TC, typename A>
    requires(std::is_fundamental_v<__canonical_storage_t<A>>)
struct StorageProvider<TC, A> {
    using type = __stack__storage<TC, __canonical_storage_t<A>>;
};

/**
 * Storage backend abstraction to be be used as a template base class for
 * containers.
 *
 * See @ref{fp::internal::storage::BoxStorage} and
 * @ref{fp::internal::storage::StackStorage} for the real thing.
 *
 * Do not construct or manipulate this unless you know what you're doing
 */
template <typename T>
struct Storage : public StorageProvider<Storage, T>::type {
  private:
    using SP = typename StorageProvider<Storage, T>::type;
    friend SP;

  public:
    using SP::SP;
};

};  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_H
