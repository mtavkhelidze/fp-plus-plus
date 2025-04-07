#pragma once
#include <iostream>
#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#include "defs.h"
#include "functions.h"

namespace fp {

template <typename T, typename... Ts>
struct Box {
  private:
    // NOLINTNEXTLINE:avoid-c-arrays
    std::variant<std::unique_ptr<T>, std::unique_ptr<T[]>> data;

  public:
    [[nodiscard]] [[clang::annotate("nullable")]]
    auto getOrNull() const -> T* {
        if (data.index() == 0) {
            return std::get<std::unique_ptr<T>>(data).get();
        }
        // NOLINTNEXTLINE:avoid-c-arrays
        if (data.index()) { return std::get<std::unique_ptr<T[]>>(data).get(); }
        return nullptr;
    }

    explicit Box(const T& t) : data{std::make_unique<T>(t)} {}
    explicit Box(T&& t, Ts&&... ts) {
        if constexpr (sizeof...(Ts) > 0) {
            data = std::move(
              util::to_array(std::forward<T>(t), std::forward<Ts>(ts)...)
            );
        } else {
            data = std::make_unique<T>(std::move(std::forward<T>(t)));
        }
    }
    // Defaulted copy and move
    ~Box() = default;
    auto operator=(Box&&) -> Box& = default;
    auto operator=(const Box&) -> Box& = default;
    Box() = delete;
    Box(Box&&) = default;
    Box(const Box&) = default;
};

// Deduction guides
template <typename T>
Box(T&&) -> Box<std::decay_t<T>>;

Box(const char*) -> Box<std::string>;

}  // namespace fp
