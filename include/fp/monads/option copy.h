#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <print>
#include <type_traits>

template <typename U>
using CleanConst = std::add_const_t<std::remove_reference_t<U>>;

namespace fp {

template <typename A>
class Option;
template <typename A>
inline auto Some(A& a) {
    return Option(std::forward<A>(a));
}

template <typename A>
inline auto Some(A&& a) {
    return Option(std::forward<A>(a));
}

template <typename A>
inline auto None() {
    return Option<A>();
}
template <typename A>
class Option {
  private:
    std::shared_ptr<A> value;
    template <typename T>
    friend auto Some(T& a);
    template <typename T>
    friend auto Some(T&& a);
    template <typename T>
    friend auto None();

  private:
    Option() : value(nullptr) {}
    Option(A&& a) : value(std::make_shared<A>(std::forward<A>(a))) {}

  public:
    constexpr inline bool isNone() const { return !value; }
    constexpr inline bool isSome() const { return static_cast<bool>(value); }

    inline bool equals(Option<A>& other) {
        if (isNone() && other.isNone()) { return true; }
        if (isSome() && other.isSome()) { return *value == *(other.value); }
        return false;
    }

    inline bool equals(Option<A>&& other) {
        if (isNone() && other.isNone()) { return true; }
        if (isSome() && other.isSome()) { return *value == *(other.value); }
        return false;
    }

    // Satisfy Eq concept
    static bool equals(const Option<A>& lhs, const Option<A>& rhs) {
        return lhs.equals(rhs);
    }

    const A& getOrElse(const A& a) const {
        if (isSome())
            return *value;
        else
            return a;
    }

    const A& get() const {
        if (isSome())
            return *value;
        else { throw std::runtime_error("Option is None"); }
    }
    // map function to transform the value, still keeping it const
    template <typename F>
    auto map(F&& f) {
        using Result = std::invoke_result_t<F, A>;
        if (isSome()) { return Some(f(*value)); }
        return None<Result>();
    }
};

}  // namespace fp
