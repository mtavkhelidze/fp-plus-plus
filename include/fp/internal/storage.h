#ifndef FP_INTERNAL_STORAGE_H

#define FP_INTERNAL_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage_box.h>

#include <type_traits>

namespace fp::internal::storage {

template <template <typename> typename TC, typename A>
struct Backend {
    using type = std::conditional_t<
      std::is_fundamental_v<A>,  //
      StorageBox<TC, A>,         //
      StorageBox<TC, A>          //
      >;
};

template <template <typename> typename Data, typename A>
struct StorageProvider : public Backend<Data, A>::type {
  protected:
    using Base = Backend<Data, A>::type;
    using Base::Base;
    friend Data<A>;
};
};  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_H
