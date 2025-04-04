#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#pragma once

#include <functional>
#include <memory>
#include <type_traits>
#include <variant>

namespace fp {
template <typename T>
struct Option;

template <typename T>
    requires(!std::is_lvalue_reference_v<T>)
inline constexpr Option<T> Some(T&& rv) {
    return Option<T>::some_from_rvalue(std::forward<T>(rv));
}
template <typename T>
inline constexpr Option<T&> Some(const T& lv) {
    return Option<T&>::some_from_lvalue(lv);
}
// template <typename T>
// inline constexpr Option<T> Some(T* value) {
//     return Option<T>().mk_some(value);
// }
template <typename T = Nothing>
inline constexpr Option<T> None() {
    return Option<T>::mk_none();
}

template <typename T>
struct Option {
  public:
    inline auto getOrElse(T alternative) const {
        if (std::holds_alternative<std::nullptr_t>(data)) {
            return alternative;
        }
        if constexpr (std::is_lvalue_reference_v<T>) {
            return std::get<std::reference_wrapper<std::remove_reference_t<T>>>(
                     data
            )
              .get();
        } else {
            return std::get<std::remove_reference_t<T>>(data);
        }
    }

  private:
    using ValueType = std::variant<
      std::remove_reference_t<T>,
      std::reference_wrapper<std::remove_reference_t<T>>,
      std::remove_reference_t<T>*, std::nullptr_t>;

    ValueType data;
    Option(ValueType&& v) : data(std::move(v)) {}

    static Option<T> some_from_rvalue(T&& rv) {
        return Option<T>(ValueType(std::forward<T>(rv)));
    }

    static Option<T&> some_from_lvalue(const T& lv) {
        return Option<T&>(ValueType(std::ref(lv)));
    }

    // Default version for types other than void
    static Option<T> mk_none() { return Option<T>(ValueType(nullptr)); }

    // Friends
    template <typename U>
    friend constexpr Option<U> None();

    template <typename U>
    friend constexpr Option<U&> Some(const U& value);

    template <typename U>
        requires(!std::is_lvalue_reference_v<U>)
    friend constexpr Option<U> Some(U&& value);
    // friend Option<T> Some<>(T* value);
    // friend Option<T> Some<>(std::nullptr_t);
};

}  // namespace fp
