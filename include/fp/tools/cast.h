#ifndef FP_TOOLS_TC_H
#define FP_TOOLS_TC_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/data/nothing.h>

#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace fp::tools::cast {
namespace __internal {
    template <typename T>
    struct __fp_type_cast;
}

/// Obtain a type that T becomes after put into @ref{fp::internal::box::Box<T>}
template <typename T>
using fp_cast = typename __internal::__fp_type_cast<T>::type;

namespace __internal {

    template <typename T>
    struct __fp_type_cast_spec {
        using type = std::decay_t<T>;
    };

    // const char* / char* → std::string
    template <>
    struct __fp_type_cast_spec<const char*> {
        using type = std::string;
    };

    template <>
    struct __fp_type_cast_spec<char*> {
        using type = std::string;
    };

    // char arrays → std::string
    template <std::size_t N>
    struct __fp_type_cast_spec<const char (&)[N]> {
        using type = std::string;
    };

    template <std::size_t N>
    struct __fp_type_cast_spec<char (&)[N]> {
        using type = std::string;
    };

    // U[N] (non-char) → std::vector<U>
    template <typename U, std::size_t N>
        requires(!std::same_as<std::decay_t<U>, char>)
    struct __fp_type_cast_spec<U[N]> {
        using type = std::vector<std::decay_t<U>>;
    };

    template <typename U, std::size_t N>
        requires(!std::same_as<std::decay_t<U>, char>)
    struct __fp_type_cast_spec<const U (&)[N]> {
        using type = std::vector<std::decay_t<U>>;
    };

    // U[0] (non-char) → std::vector<U>
    template <typename U, std::size_t N>
        requires(sizeof(N) == 0 && !std::same_as<std::decay_t<U>, char>)
    struct __fp_type_cast_spec<U[N]> {
        using type = std::vector<std::decay_t<U>>;
    };

    template <typename U, std::size_t N>
        requires(sizeof(N) == 0 && !std::same_as<std::decay_t<U>, char>)
    struct __fp_type_cast_spec<const U (&)[N]> {
        using type = std::vector<std::decay_t<U>>;
    };

    // std::array<T, N> → std::vector<T>
    template <typename T, std::size_t N>
    struct __fp_type_cast_spec<std::array<T, N>> {
        using type = std::vector<std::decay_t<T>>;
    };

    // std::tuple<U...> → tuple<U...>
    template <typename... Ts>
    struct __fp_type_cast_spec<std::tuple<Ts...>> {
        using type = std::tuple<std::remove_cvref_t<Ts>...>;
    };

    // void / nullptr → Nothing
    template <>
    struct __fp_type_cast_spec<void> {
        using type = fp::data::nothing::Nothing;
    };

    template <>
    struct __fp_type_cast_spec<std::nullptr_t> {
        using type = fp::data::nothing::Nothing;
    };

    // std::optional<void> → std::optional<Nothing>
    template <>
    struct __fp_type_cast_spec<std::optional<void>> {
        using type = std::optional<fp::data::nothing::Nothing>;
    };

    // Main dispatch (removes cvref and applies the mapping)
    template <typename T>
    struct __fp_type_cast : __fp_type_cast_spec<std::remove_cvref_t<T>> {};

}  // namespace __internal

}  // namespace fp::tools::cast
#endif  // FP_TOOLS_TC_H
