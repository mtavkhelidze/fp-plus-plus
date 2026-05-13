#ifndef __FP_INTERNAL_STORAGE_BOX_H
#define __FP_INTERNAL_STORAGE_BOX_H
#include <initializer_list>
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/types.h>
#include <fp/internal/meta/instance.h>

#include <concepts>
#include <cstddef>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>

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

    // initializer_list → Vector
    template <typename U>
    Box(std::initializer_list<U> il)
        requires(std::copy_constructible<U>)
    {
        using Normalised = typename decltype(fp::internal::storage::Box(
          std::declval<U>()
        ))::kind;
        data::Vector<Normalised> v;
        v.reserve(il.size());
#pragma unroll 256
        for (const auto& elem : il) {
            v.push_back(fp::internal::storage::Box(elem).get());
        }
        data = std::make_shared<T>(std::move(v));
    }

    // Tuple helper
  private:
    template <typename... Ts, std::size_t... Is>
    static auto __normalise_tuple(
      std::tuple<Ts...> t, std::index_sequence<Is...>
      /*unused*/
    ) {
        return std::make_tuple(
          fp::internal::storage::Box(std::get<Is>(std::move(t))).get()...
        );
    }

  public:
    // Varargs to tuple
    template <typename U, typename... Us>
        requires(sizeof...(Us) > 0)
    explicit Box(U&& u, Us&&... us) {
        auto raw = std::make_tuple(std::forward<U>(u), std::forward<Us>(us)...);
        auto normalised = __normalise_tuple(
          std::move(raw), std::make_index_sequence<1 + sizeof...(Us)>{}
        );
        data = std::make_shared<T>(std::move(normalised));
    }

    // Tuple directly
    template <typename... Ts>
    explicit Box(std::tuple<Ts...> t) {
        auto normalised = __normalise_tuple(
          std::move(t), std::make_index_sequence<sizeof...(Ts)>{}
        );
        data = std::make_shared<T>(std::move(normalised));
    }

    // Value (not pointer)
    explicit Box(const T& t)
        requires(!std::is_pointer_v<T> && !meta::instance::is_tuple<T>)
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

    // Other
    ~Box() = default;
    auto operator=(Box&&) noexcept -> Box& = delete;
    auto operator=(const Box&) -> Box& = default;
    Box(Box&&) noexcept = delete;
    Box(const Box&) = default;
};

// CTAD

// Anything
template <typename U>
Box(const U&&) -> Box<std::decay_t<U>>;
template <typename U>
Box(const U&) -> Box<std::decay_t<U>>;

// Literal strings (Box("str")), converted to String
Box(const char*) -> Box<data::String>;

template <typename U, std::size_t N>
    requires(std::same_as<std::decay_t<U>, char>)
Box(const U (&)[N]) -> Box<data::String>;

// c-style arrays, not char*

template <typename U, std::size_t N>
    requires(!std::same_as<std::decay_t<U>, char>)
Box(const U (&)[N]) -> Box<data::Vector<std::decay_t<U>>>;

// Varargs to tuple
template <typename U, typename... Us>
    requires(sizeof...(Us) > 0)
Box(U&&, Us&&...) -> Box<data::Tuple<
  typename decltype(Box(std::declval<U>()))::kind,
  typename decltype(Box(std::declval<Us>()))::kind...>>;

// Tuple directl
template <typename... Ts>
Box(std::tuple<Ts...>)
  -> Box<data::Tuple<typename decltype(Box(std::declval<Ts>()))::kind...>>;

// initializer list
template <typename U>
Box(std::initializer_list<U>) -> Box<data::Vector<std::decay_t<U>>>;

// NOLINTEND(modernize-avoid-c-arrays,hicpp-avoid-c-arrays,cppcoreguidelines-avoid-c-arrays)
}  // namespace fp::internal::storage

#endif  // __FP_INTERNAL_STORAGE_BOX_H
