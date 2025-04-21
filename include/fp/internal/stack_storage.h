#ifndef FP_INTERNAL_STACK_STORAGE_H
#define FP_INTERNAL_STACK_STORAGE_H
#include <utility>
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <iostream>
#include <type_traits>

namespace fp::internal::storage::stack {

/**
 * Internal stack-based value storage abstraction.
 *
 * This class is designed to hold simple, fundamental types directly on the
 * stack. It is not intended for direct construction — values must be created
 * via the static `store()` method.
 *
 * ## Constraints:
 * - StackStorage instances can only be created via the static `store()` method.
 * - Copying and moving are both allowed as the underlying value is trivially
 *   copyable.
 * - Values can only be accessed via `getOrElse(const A&)`.
 *
 * Do not construct or manipulate this class directly.
 */
template <template <typename> typename TC, typename A>
    requires std::is_fundamental_v<A>
struct StackStorage {
  private:
    A value;

  protected:
    explicit StackStorage(A&& a) : value(std::forward<A>(a)) {}

  protected:
    template <typename T>
    static auto store(T&& x) -> TC<std::decay_t<T>> {  //
        return TC<std::decay_t<T>>(std::forward<std::decay_t<T>>(x));
    };

  public:
    auto getOrElse(const A&) const -> A {  //
#ifdef FP_PLUS_PLUS_TESTING
        std::cout << "Simple value: " << value << std::endl;
#endif
        return value;
    }
};
}  // namespace fp::internal::storage::stack
#endif  // FP_INTERNAL_STACK_STORAGE_H
