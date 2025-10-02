#ifndef FP_INTERNAL_MIXINS_WITH_VALUE_H
#define FP_INTERNAL_MIXINS_WITH_VALUE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/storage_box.h>
#include <fp/internal/storage/storage_stack.h>

#include <type_traits>

namespace fp::core::mixins {

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
template <typename F>
struct WithValue : private Backend<F>::type {
  private:
    using Base = typename Backend<F>::type;
    using Base::Base;

  public:
    /**
     * Constructs an instance of F from a raw C++ value of type T using the
     * backend storage returning F<A>.
     *
     * Example:
     *   auto val = F::apply(42);  // Constructs F<int> from int 42
     */
    template <typename T>
    static constexpr auto apply(T&& value) -> F {
        return F{Base::put(std::forward<T>(value))};
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
};  // namespace fp::core::mixins

#endif  // FP_INTERNAL_MIXINS_WITH_VALUE_H
