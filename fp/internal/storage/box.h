#ifndef FP_INTERNAL_STORAGE_BOX_H
#define FP_INTERNAL_STORAGE_BOX_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/defs.h>

#include <cstddef>
#include <memory>
#include <vector>

// NOLINTBEGIN(hicpp-avoid-c-arrays,cppcoreguidelines-avoid-c-arrays)

namespace fp::internal::storage {
/**
 * Box: mean and possesive data storage. See `fp/internal/storage/readme.md` for
 * details.
 */
template <typename T>
struct FP_ALIGN_PACKED_16 Box {
  private:
    std::shared_ptr<const T> data;

  public:
    using kind = T;

    // --- Accessors
    [[nodiscard]]
    constexpr auto get() const -> const T& {
        return *data;
    }
    [[nodiscard]] constexpr auto empty() const -> bool { return !data; }
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

    // Move-only
    explicit Box(T&& t)
        requires(
          std::is_move_constructible_v<T> && !std::is_copy_constructible_v<T>
        )
        : data{std::make_shared<T>(std::move(t))} {}

    // nothing (default comes here)
    explicit Box() : data(nullptr) {}

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
        T t(std::forward<U>(u), std::forward<Us>(us)...);
        data = std::make_shared<T>(t);
    }
    // --- Other constructors
    ~Box() = default;
    auto operator=(Box&&) noexcept -> Box& = delete;
    auto operator=(const Box&) -> Box& = default;
    Box(Box&&) noexcept = delete;
    Box(const Box&) = default;
};

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
    requires(!std::same_as<std::decay_t<U>, char>)
Box(const U (&)[N]) -> Box<std::vector<std::decay_t<U>>>;

// varargs
template <typename U, typename... Us>
    requires(sizeof...(Us) > 0)
Box(U&&, Us&&...) -> Box<std::tuple<std::decay_t<U>, std::decay_t<Us>...>>;

// NOLINTEND(hicpp-avoid-c-arrays,cppcoreguidelines-avoid-c-arrays)
}  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STORAGE_BOX_H
