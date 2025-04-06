#ifndef __FP_PLUS_PLUS__
#error "This file must be included from "fp/fp.h"
#endif

#pragma once

#include <array>
#include <memory>

#include "defs.h"

namespace fp {

template <typename T>
struct Box {
  private:
    std::shared_ptr<T> data;

  public:
    inline auto get() const -> const T* { return static_cast<T*>(data.get()); }

    template <std::size_t N>
    inline explicit Box(const std::array<T, N>& t)
        requires(N > 0)
        : data(std::make_shared<std::array<T, N>>(t)) {}
    inline explicit Box(T&& t) :
        data(std::make_shared<T>(std::forward<T>(t))) {}
    inline explicit Box(const T& t) : data(std::make_shared<T>(t)) {}

    // Defaulted copy and move
    ~Box() = default;
    auto operator=(Box&&) -> Box& = default;
    auto operator=(const Box&) -> Box& = default;
    Box() = delete;
    Box(Box&&) = default;
    Box(const Box&) = default;
};

template <typename T>
Box(T&&) -> Box<std::decay_t<T>>;
Box(const char*) -> Box<const char*>;

}  // namespace fp
