#ifndef FP_INTERNAL_STORAGE_H

#define FP_INTERNAL_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/storage_box.h>
#include <fp/internal/storage/storage_stack.h>
#include <fp/tools/cast.h>

#include <type_traits>

namespace fp::mixins::storage {

template <typename T>
using fp_cast = fp::tools::cast::fp_cast<T>;

template <
  template <typename> typename TC,
  typename A,
  bool = std::is_fundamental_v<A>>
struct __backend;

template <template <typename> typename TC, typename A>
struct __backend<TC, A, true> {
    using type = internal::storage::StorageStack<TC, A>;
};

template <template <typename> typename TC, typename A>
struct __backend<TC, A, false> {
    using type = internal::storage::StorageBox<TC, A>;
};

template <template <typename> typename TC, typename A>
using Backend = __backend<TC, A>;

/**
 * Mixin for objects with storage backend and ::apply.
 */
template <template <typename> typename DataClass, typename A>
struct WithStorage : private Backend<DataClass, A>::type {
  private:
    using Base = typename Backend<DataClass, A>::type;
    using Base::Base;

  public:
    template <typename T>
    static constexpr auto apply(T&& value) -> DataClass<fp_cast<T>> {
        return DataClass{Base::put(value)};
    }
    constexpr auto has_value() const noexcept -> bool {  //
        return !this->empty();
    }
    constexpr auto value() const noexcept -> const A& {  //
        return this->get();
    }
    // Eq
    constexpr auto equals(const WithStorage& other) const noexcept -> bool {
        static_assert(
          std::equality_comparable<A>,
          "The type A must support operator== to use equals()."
        );
        return this->value() == other.value();
    }
#ifdef FP_PLUS_PLUS_TESTING
  public:
    constexpr auto is_box() const -> bool {
        return strcmp(this->_tag, "StorageBox") == 0;
    }
    constexpr auto is_stack() const -> bool {
        return strcmp(this->_tag, "StorageStack") == 0;
    }
#endif  // FP_PLUS_PLUS_TESTING
};
};  // namespace fp::mixins::storage

#endif  // FP_INTERNAL_STORAGE_H
