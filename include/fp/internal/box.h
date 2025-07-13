#ifndef FP_KERNEL_BOX_H
#define FP_KERNEL_BOX_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/core/nothing.h>
#include <fp/prelude/defs.h>

#include <cstddef>
#include <memory>
#include <optional>
#include <variant>
#include <vector>

namespace fp::internal::box {
using fp::core::Nothing;

/**
 * Generic value holder (`Box`) that wraps a value of type `T`, enforcing
 * shared ownership and idiot-resistant immutability.
 *
 * - The boxed value is heap-allocated and managed via `shared_ptr<const T>`.
 * - Once boxed, the value cannot be modified through any API exposed by `Box`.
 * - This prevents accidental or intentional mutation through normal usage.
 * - True immutability depends on `T` not exposing mutating behavior via
 *   `mutable` fields or internal `const_cast` tricks.
 * - Move construction and move assignment are disallowed to preserve
 * immutability and clarity of ownership.
 * - Copying is allowed and cheap, as it only increments the reference count of
 * the underlying `shared_ptr`.
 * - Special constructors handle pointer types, tuples, C-style arrays, and
 * null.
 * - This approach prioritizes immutability-by-design over absolute enforcement.
 */
template <typename T>
struct FP_ALIGN_PACKED_16 Box {
  private:
    std::shared_ptr<const T> data;
    static constexpr auto __nothing = Nothing();

  public:
    using kind = T;

    // --- Accessors
    [[nodiscard]]
    constexpr auto get() const -> const T& {
        return *data;
    }
    constexpr auto empty() const -> bool {
        if constexpr (std::is_same_v<T, Nothing>) {
            return true;
        } else {
            return false;
        }
    }
    // --- constructors

    // Value (not pointer)
    explicit Box(const T& t)
        requires(!std::is_pointer_v<T>)
        : data{std::make_shared<T>(t)} {}

    // Pointer: shared
    explicit Box(std::shared_ptr<T> ptr) : data(std::move(ptr)) {}

    // Pointer: unique
    explicit Box(std::unique_ptr<T>& ptr) : data(std::move(ptr)) {}

    // Pointer: raw
    explicit Box(T ptr)
        requires(std::is_pointer_v<T>)
        : data(std::make_shared<T>(std::move(ptr))) {}

    // Pointer: null
    explicit Box(std::nullopt_t)
        requires(std::is_null_pointer_v<T>)
        : data(std::make_shared<Nothing>(__nothing)) {}

    // Move-only
    explicit Box(T&& t)
        requires(
          std::is_move_constructible_v<T> && !std::is_copy_constructible_v<T>
        )
        : data{std::make_shared<T>(std::move(t))} {}

    // nothing (default comes here)
    explicit Box() : data(std::make_shared<Nothing>(__nothing)) {}

    // c-style array, not char*
    template <typename U, std::size_t N>
        requires(
          !std::same_as<std::decay_t<U>, char>
          && requires(const U (&a)[N]) { T(std::begin(a), std::end(a)); }
        )
    explicit Box(const U (&arr)[N]) {
        T v(std::begin(arr), std::end(arr));
        data = std::make_shared<T>(v);
    }
    // tuple
    template <typename U, typename... Us>
        requires(
          std::is_same_v<T, std::tuple<std::decay_t<U>, std::decay_t<Us>...>>
        )
    explicit Box(U&& u, Us&&... us) {
        T t(u, us...);
        data = std::make_shared<T>(t);
    }
    // --- Other constructors
    ~Box() = default;
    auto operator=(Box&&) noexcept -> Box& = delete;
    auto operator=(const Box&) -> Box& = default;
    Box(Box&&) noexcept = delete;
    Box(const Box&) = default;
};  // namespace fp::internal::box

// Anything
template <typename U>
Box(const U&&) -> Box<std::decay_t<U>>;
template <typename U>
Box(const U&) -> Box<std::decay_t<U>>;

// Literal strings (Box b = "str" or Box("str")), converted automatically to
// string
Box(const char*) -> Box<std::string>;

template <typename U, std::size_t N>
    requires(std::same_as<std::decay_t<U>, char>)
Box(const U (&)[N]) -> Box<std::string>;

// c-style arrays, bar char*
template <typename U, std::size_t N>
    requires(!std::same_as<std::decay<U>, char>)
Box(const U (&)[N]) -> Box<std::vector<std::decay_t<U>>>;

// varargs
template <typename U, typename... Us>
    requires(sizeof...(Us) > 0)
Box(U&&, Us&&...) -> Box<std::tuple<std::decay_t<U>, std::decay_t<Us>...>>;

// Empty box
Box() -> Box<Nothing>;
Box(std::nullptr_t) -> Box<Nothing>;

}  // namespace fp::internal::box
#endif  // FP_KERNEL_BOX_H
