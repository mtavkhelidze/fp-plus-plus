#ifndef FP_KERNEL_BOX_H
#define FP_KERNEL_BOX_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/prelude.h>

#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

namespace fp::kernel::box {
using namespace fp::prelude;

template <typename T, typename... Ts>
struct FP_ALIGN_PACKED_16 Box {
  private:
    std::variant<std::shared_ptr<T>, std::vector<T>, Nothing> data = Nothing();

  public:
    // --- Accessors
    [[nodiscard]] [[clang::annotate("nullable")]]
    auto getOrNull() const -> const T* {
        if (data.index() == 0) {
            return std::get<std::shared_ptr<T>>(data).get();
        }
        if (data.index() == 1) {
            return std::get<std::vector<T>>(data).data();
        }
        return nullptr;
    }
    // --- constructors
    // Concrete
    explicit Box(const T& t)
        requires(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>)
        : data{std::make_shared<T>(t)} {}
    // Pointer: shared
    explicit Box(std::shared_ptr<T> ptr) : data(std::move(ptr)) {}
    // Pointer: unique
    explicit Box(std::unique_ptr<T>& ptr) : data(std::move(ptr)) {}
    // Pointer: raw
    explicit Box(T ptr)
        requires(std::is_pointer_v<T>)
        : data(std::make_shared<T>(std::move(ptr))) {
        static_assert(!std::is_null_pointer_v<T>, "nullptr is not allowed");
    }
    // Varargs; creates an array
    explicit Box(const T&& t, Ts&&... ts)
        requires(sizeof...(Ts) > 0)
    {
        std::vector<T> vec = {std::move(t), std::move(ts)...};
        data = std::move(vec);
    }
    // Move-only
    explicit Box(T&& t)
        requires(
          std::is_move_constructible_v<T> && !std::is_copy_constructible_v<T>
        )
        : data{std::make_shared<T>(std::move(t))} {}

    // nothing (default comes here)
    explicit Box<Nothing>() : data(Nothing()) {}

    // --- Other constructors
    ~Box() = default;
    auto operator=(Box&&) -> Box& = default;
    auto operator=(const Box&) -> Box& = delete;
    Box(Box&&) = default;
    Box(const Box&) = delete;
};

// Deduction guides
template <typename T>
Box(T&&) -> Box<std::decay_t<T>>;

template <typename U, std::size_t N>
Box(const std::array<U, N>&) -> Box<U*>;

Box(const char*) -> Box<std::string>;

Box() -> Box<Nothing>;

Box(std::nullptr_t) -> Box<Nothing>;
}  // namespace fp::kernel::box
#endif  // FP_KERNEL_BOX_H
