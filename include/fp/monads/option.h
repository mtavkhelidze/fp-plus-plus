#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#pragma once

#include <functional>
#include <type_traits>
#include <variant>

auto up = std::unique_ptr<int>(new int(5));
auto& uup = up;

namespace fp {
template <typename T>
struct Option;

template <typename T>
inline constexpr Option<T> Some(T&& rv) {
    return Option<T>::some_from_rvalue(std::forward<T>(rv));
}

template <typename T>
inline constexpr Option<T&> Some(const T& lv) {
    return Option<T&>::some_from_lvalue(lv);
}

template <typename T>
inline constexpr Option<T*> Some(T* ptr) {
    return Option<T*>::some_from_pointer(ptr);
}

template <typename T = Nothing>
inline constexpr Option<T> None() {
    return Option<T>::mk_none();
}

template <typename T>
struct Option {
  public:
    inline const auto& getOrElse(T&& defaultValue) const {
        try {
            switch (data.index()) {
                case 0:  // holds T (value type)
                    return std::get<std::remove_reference_t<T>>(data);
                case 1:  // holds T& (reference)
                    return getRef();
                case 2:  // holds T* (pointer)
                    return *std::get<std::remove_reference_t<T>*>(data);
                default:  // holds nullptr (Nothing case)
                    throw std::forward<T>(defaultValue);
            }
        } catch (...) { return std::forward<T>(defaultValue); }
    }

  private:
    using ValueType = std::variant<
      std::remove_reference_t<T>,
      std::reference_wrapper<std::remove_reference_t<T>>,
      std::remove_reference_t<T>*, std::nullptr_t>;

    ValueType data;
    inline explicit Option<T>(ValueType&& v) : data(std::move(v)) {}

    inline auto& getRef() const {
        return std::get<std::reference_wrapper<std::remove_reference_t<T>>>(data
        )
          .get();
    }

    static Option<T> some_from_pointer(T ptr) {
        return Option<T>(ValueType((std::remove_reference_t<T>*)ptr));
    }

    static Option<T> some_from_rvalue(T&& rv) {
        return Option<T>(ValueType(std::forward<T>(rv)));
    }
    static Option<T&> some_from_lvalue(const T& lv) {
        return Option<T&>(ValueType(std::ref(lv)));
    }

    static Option<T> mk_none() { return Option<T>(ValueType(nullptr)); }

    // Friends
    template <typename U>
    friend constexpr Option<U> None();

    template <typename U>
    friend constexpr Option<U> Some(U&& value);

    template <typename U>
    friend constexpr Option<U&> Some(const U& value);

    template <typename U>
    friend constexpr Option<U*> Some(U* ptr);

#ifdef __FP_PP_TESTING
    // never mind those, only used for testing
  public:
    std::string type_name() const {
        if (std::holds_alternative<std::nullptr_t>(data)) { return "Nothing"; }

        // Use index() to check the active type
        switch (data.index()) {
            case 0:
                return "T";  // Index for the first type
                             // (std::remove_reference_t<T>)
            case 1:
                return "T&";  // Index for the second type
                              // (std::reference_wrapper<std::remove_reference_t<T>>)
            case 2:
                return "T*";  // Index for the third type
                              // (std::remove_reference_t<T>*)
            default:
                return "This should not happen! Call technical personnel.";
        }
    }
#endif  // __FP_PP_TESTING
};

}  // namespace fp
