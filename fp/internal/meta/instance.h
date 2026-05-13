#ifndef __FP__INTERNAL_META_INSTANCE_H
#define __FP__INTERNAL_META_INSTANCE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP

#include <fp/data/types.h>
#include <fp/internal/meta/tools.h>

#include <cstddef>
#include <type_traits>

namespace fp::internal::meta::instance {

namespace {
    template <typename A>
    struct _type_class_instance {
        static constexpr std::size_t value = 0;
    };
    template <template <typename...> typename F, typename... A>
    struct _type_class_instance<F<A...>> {
        static constexpr std::size_t value = sizeof...(A);
    };

    template <typename A>
    struct _type_class_unary_instance : std::false_type {
        static_assert(
          tools::always_false<A>,
          "F must be of the form F<A> (i.e.std::optional<int>)."
        );
    };
    template <template <typename> typename F, typename A>
    struct _type_class_unary_instance<F<A>> : std::true_type {};

    template <typename A>
    struct _type_class_binary_instance : std::false_type {
        static_assert(
          tools::always_false<A>,
          "F must be of the form F<A, B> (i.e.std::pair<int, float>)."
        );
    };
    template <template <typename, typename> typename F, typename A, typename B>
    struct _type_class_binary_instance<F<A, B>> : std::true_type {};

    template <typename>
    struct _type_class_unary_template;

    template <template <typename> typename F, typename A>
    struct _type_class_unary_template<F<A>> {
        template <typename X>
        using type = F<X>;
    };

    template <typename A>
    struct unary_template_type {
        template <typename X>
        using type = typename _type_class_unary_template<
          std::decay_t<A>>::template type<X>;
    };
    template <typename T>
    struct _is_tuple : std::false_type {};

    template <typename... Ts>
    struct _is_tuple<data::Tuple<Ts...>> : std::true_type {};
}  // namespace

template <typename F>
inline constexpr bool is_instance =
  _type_class_instance<std::decay_t<F>>::value > 0;

template <typename T>
inline constexpr bool is_tuple = _is_tuple<std::decay_t<T>>::value;

template <typename F>
inline constexpr bool is_unary_instance =
  _type_class_unary_instance<std::decay_t<F>>::value;

template <typename F>
inline constexpr bool is_binary_instance =
  _type_class_binary_instance<std::decay_t<F>>::value;

template <typename F>
inline constexpr std::size_t instance_arity =
  _type_class_instance<std::decay_t<F>>::value;

}  // namespace fp::internal::meta::instance

#endif  // __FP__INTERNAL_META_INSTANCE_H
