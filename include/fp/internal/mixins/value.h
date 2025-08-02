#ifndef FP_INTERNAL_MIXINS_VALUE_H
#define FP_INTERNAL_MIXINS_VALUE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/storage_box.h>
#include <fp/internal/storage/storage_stack.h>

#include <type_traits>

namespace fp::internal::mixins {

template <
  typename TC,
  bool = std::is_fundamental_v<fp::tools::inner_type::fp_inner_type<TC>>>
struct __backend;

template <typename TC>
struct __backend<TC, true> {
    using type = internal::storage::StorageStack<TC>;
};

template <typename TC>
struct __backend<TC, false> {
    using type = internal::storage::StorageBox<TC>;
};

template <typename TC>
using Backend = __backend<TC>;

/**
 * Mixin for objects with storage backend and ::apply.
 */
template <typename DataClass>
struct WithValue : private Backend<DataClass>::type {
  private:
    using Base = typename Backend<DataClass>::type;
    using Base::Base;

  public:
    /**
     * This is a static constructor similar to Scala's `apply`, allowing
     * creation of DataClass instances via `DataClass::apply(value)`.
     *
     * Note: This is not related to the `Applicative::pure` typeclass function,
     * though it may be used internally by `pure`.
     */
    template <typename T>
    static constexpr auto apply(T&& value) -> DataClass {
        return DataClass{Base::put(std::forward<T>(value))};
    }
    constexpr auto value() const noexcept -> auto& { return this->get(); }

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
};  // namespace fp::internal::mixins

#endif  // FP_INTERNAL_MIXINS_VALUE_H
