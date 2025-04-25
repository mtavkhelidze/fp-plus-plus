#ifndef FP_INTERNAL_STORAGE_H

#define FP_INTERNAL_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/storage_box.h>
#include <fp/internal/storage/storage_stack.h>

#include <type_traits>

namespace fp::internal::storage {

template <
  template <typename> typename TC,
  typename A,
  bool = std::is_fundamental_v<A>>
struct __backend;

template <template <typename> typename TC, typename A>
struct __backend<TC, A, true> {
    using type = StorageStack<TC, A>;
};

template <template <typename> typename TC, typename A>
struct __backend<TC, A, false> {
    using type = StorageBox<TC, A>;
};

template <template <typename> typename TC, typename A>
using Backend = __backend<TC, A>;

template <template <typename> typename Data, typename A>
struct StorageProvider : private Backend<Data, A>::type {
  private:
    using Base = Backend<Data, A>::type;
    using Base::Base;

    // this foreces the coomon interface onto Backends
  protected:
    inline auto have_value() const noexcept -> bool {  //
        return !this->empty();
    }
    inline auto retrieve() const noexcept -> const A& {  //
        return this->get();
    }
    inline static constexpr auto store(
      auto&& x
    ) noexcept(std::is_nothrow_move_constructible_v<A>) {  //
        return Base::put(x);
    }
#ifdef FP_PLUS_PLUS_TESTING
  public:
    inline constexpr auto is_box() -> bool {
        return strcmp(this->_tag, "StorageBox") == 0;
    }
    inline constexpr auto is_stack() -> bool {
        return strcmp(this->_tag, "StorageStack") == 0;
    }
#endif  // FP_PLUS_PLUS_TESTING
};
};  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_H
