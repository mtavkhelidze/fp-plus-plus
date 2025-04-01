#ifndef ___FP_PP_OPTION_H__
#define ___FP_PP_OPTION_H__

#ifndef __FP_PLUS_PLUS__
#error "This file must be included from fp/fp"
#endif

#include <functional>
#include <iostream>
#include <optional>
#include <type_traits>

namespace fp {

template <typename A>
class Option;

template <typename A>
inline const Option<A> Some(const A& a) {
    return Option<A>(a);
}

template <typename A>
inline const Option<A> None() {
    return Option<A>(std::nullopt);
}


// template <typename T>
// struct is_option : std::false_type {};

// template <typename A>
// struct is_option<Option<A>> : std::true_type {};

// template <typename T>
// constexpr bool is_option_v = is_option<T>::value;

template <typename A>
class Option {
  private:
    std::optional<A> value;

  public:
    template <typename T>
    friend const Option<T> Some(const T& a);

    template <typename T>
    friend const Option<T> None();

  protected:
    explicit Option(std::optional<A> v) : value(v) {}

  public:
    constexpr inline bool isNone() const { return !value.has_value(); }
    constexpr inline bool isSome() const { return value.has_value(); }

    // @misha: put this into concept Eq some day
    constexpr inline bool equals(const Option<A>& other) const {
        if (isNone() && other.isNone()) { return true; }
        if (isSome() && other.isSome()) { return *value == *other.value; }
        return false;
    }
    const A& getOrElse(const A& a) const {
        if (isSome())
            return *value;
        else
            return a;
    }

    A get() const {
        if (isSome())
            return *value;
        else {
            throw std::runtime_error("Option is None");  // Throws an exception
        }
    }

  public:
    template <typename F>
    auto map(F&& f) const -> Option<std::invoke_result_t<F, A>> {
        if (isSome()) {
            return Some(f(*value));
        } else {
            return None<std::invoke_result_t<F, A>>();
        }
    }

    //     template <typename F>
    //     auto flatMap(F&& f) const -> typename std::invoke_result_t<F, A> {
    //         using ReturnType = typename std::invoke_result_t<F, A>;

    //         static_assert(
    //           is_option_v<ReturnType>, "The callable must return an Option
    //           type."
    //         );

    //         if (isSome()) {
    //             return f(std::get<A>(value));
    //         } else {
    //             return ReturnType::None();
    //         }
    //     }
};

}  // namespace fp
#endif  // ___FP_PP_OPTION_H__
