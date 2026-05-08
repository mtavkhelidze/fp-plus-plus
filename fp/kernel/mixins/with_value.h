#ifndef __FP_KERNEL_MIXINS_WITH_VALUE_H
#define __FP_KERNEL_MIXINS_WITH_VALUE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/box_storage.h>
#include <fp/internal/storage/stack_storage.h>

#ifdef FP_PLUS_PLUS_TESTING
#include <cstring>
#endif

namespace fp::kernel::mixins {

namespace {
    template <typename FA>
    using itype = internal::meta::inner_type::inner_type<FA>;

    template <typename FA, bool = std::is_fundamental_v<itype<FA>>>
    struct _backend;

    template <typename FA>
    struct _backend<FA, true> {
        using type = internal::storage::StorageStack<FA>;
    };

    template <typename FA>
    struct _backend<FA, false> {
        using type = internal::storage::StorageBox<FA>;
    };

    template <typename FA>
    using Backend = _backend<FA>;
}  // namespace

/**
 * Mixin for objects with storage backend and ::apply.
 */
template <typename FA>
struct WithValue : private Backend<FA>::type {
  private:
    using Base = typename Backend<FA>::type;
    using Base::Base;

  protected:
    /**
     * Constructs an instance of F from a raw C++ value of type T using the
     * backend storage returning F<A>.
     *
     * Example:
     *   auto val = F::apply(42);  // Constructs F<int> from int 42
     */
    template <typename A>
    static constexpr auto apply(A&& value) -> FA {
        return FA{Base::put(std::forward<A>(value))};
    }
    constexpr auto value() const noexcept -> auto& { return this->get(); }

#ifdef FP_PLUS_PLUS_TESTING
    [[nodiscard]] constexpr auto is_box() const -> bool {
        return strcmp(this->_tag, "StorageBox") == 0;
    }
    [[nodiscard]] constexpr auto is_stack() const -> bool {
        return strcmp(this->_tag, "StorageStack") == 0;
    }
#endif  // FP_PLUS_PLUS_TESTING
};
};  // namespace fp::kernel::mixins

#endif  // __FP_KERNEL_MIXINS_WITH_VALUE_H
