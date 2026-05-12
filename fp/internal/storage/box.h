#ifndef __FP_INTERNAL_STORAGE_BOX_H
#define __FP_INTERNAL_STORAGE_BOX_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/types.h>

#include <concepts>
#include <cstddef>
#include <memory>
#include <type_traits>

// NOLINTBEGIN(modernize-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-avoid-c-arrays)

namespace fp::internal::storage {
/**
 * Box: mean and possessive data storage. See `fp/internal/storage/readme.md`
 * for details.
 */
template <typename T>
struct alignas(16) [[gnu::packed]] Box {
  private:
    std::shared_ptr<const T> data;

  public:
    using kind = T;

    // --- Accessors
    [[nodiscard]]
    auto get() const -> const T& {
        return *data;
    }

    [[nodiscard]]
    auto empty() const -> bool {
        return !data;
    }

    // --- constructors

    // // tuple
    // template <typename... Ts>
    // explicit Box(data::Tuple<Ts...> t) {

    // };

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
          std::is_same_v<T, data::Tuple<std::decay_t<U>, std::decay_t<Us>...>>
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
Box(const char*) -> Box<data::String>;

template <typename U, std::size_t N>
    requires(std::same_as<std::decay_t<U>, char>)
Box(const U (&)[N]) -> Box<data::String>;

// c-style arrays, bar char*
template <typename U, std::size_t N>
    requires(!std::same_as<std::decay_t<U>, char>)
Box(const U (&)[N]) -> Box<data::Vector<std::decay_t<U>>>;

// varargs
template <typename U, typename... Us>
    requires(sizeof...(Us) > 0)
Box(U&&, Us&&...) -> Box<data::Tuple<std::decay_t<U>, std::decay_t<Us>...>>;

// NOLINTEND(modernize-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-avoid-c-arrays)
}  // namespace fp::internal::storage

#endif  // __FP_INTERNAL_STORAGE_BOX_H
