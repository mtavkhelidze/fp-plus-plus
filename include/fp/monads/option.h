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

// Friend function definitions to wrap a value inside Option
template <typename T>
inline constexpr Option<T> Some(T&& value) {
    return Option<T>::mk_some(std::forward<T>(value));
}

// template <typename T>
// inline constexpr Option<T> Some(const T& value) {
//     return Option<T>().mk_some(value);
// }

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
        return std::get<T>(data);
    }

  private:
    using ValueType =
      std::variant<T, std::reference_wrapper<T>, T*, std::nullptr_t>;
    ValueType data;
    Option(ValueType&& v) : data(std::move(v)) {}

    static Option<T> mk_some(T&& value) {
        return Option<T>(ValueType(std::forward<T>(value)));
    }
    // Default version for types other than void
    static Option<T> mk_none() { return Option<T>(ValueType(nullptr)); }

    // Option<T> mk_some(const T& value);
    // Option<T> mk_some(T* value);
    // Option<T> mk_some(std::nullptr_t);

    // Friends
    friend Option<T> Some<>(T&& value);
    friend Option<T> None<>();
    // friend Option<T> Some<>(const T& value);
    // friend Option<T> Some<>(T* value);
    // friend Option<T> Some<>(std::nullptr_t);
};

}  // namespace fp
