#ifndef FP_TOOLS_INSTANCE_H
#define FP_TOOLS_INSTANCE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace fp::tools::instance {

namespace _internal {
    template <typename A>
    struct _type_class_instance {
        static constexpr std::size_t value = 0;
        static_assert(
          sizeof(A) != sizeof(A),  // NOLINT
          "TC must be of the form TC<...T> (i.e.std::optional<int>)."
        );
    };
    template <template <typename...> typename F, typename... A>
    struct _type_class_instance<F<A...>> {
        static constexpr std::size_t value = sizeof...(A);
    };

    template <typename>
    struct _type_class_unary_instance : std::false_type {
        static_assert(
          sizeof(int) != sizeof(int),  // NOLINT
          "F must be of the form F<A> (i.e.std::optional<int>)."
        );
    };
    template <template <typename> typename F, typename A>
    struct _type_class_unary_instance<F<A>> : std::true_type {};

    template <typename>
    struct _type_class_binary_instance : std::false_type {
        static_assert(
          sizeof(int) != sizeof(int),  // NOLINT
          "F must be of the form F<A, B> (i.e.std::ppair<int, float>)."
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
}  // namespace _internal

template <typename F>
inline constexpr bool fp_is_instance =
  _internal::_type_class_instance<std::decay_t<F>>::value > 0;

template <typename F>
inline constexpr bool fp_is_unary_instance =
  _internal::_type_class_unary_instance<std::decay_t<F>>::value;

template <typename F>
inline constexpr bool fp_is_binary_instance =
  _internal::_type_class_binary_instance<std::decay_t<F>>::value;

template <typename F>
inline constexpr std::size_t fp_instance_arity =
  _internal::_type_class_instance<std::decay_t<F>>::value;

template <typename F>
inline constexpr bool fp_has_no_copy = !std::is_copy_constructible_v<F>;

template <typename F>
inline constexpr bool fp_has_no_move = !std::is_move_constructible_v<F>;

template <typename F, typename A>
inline constexpr bool fp_has_no_direct_constructor =
  !std::constructible_from<F, A>;

template <typename A>
struct fp_unary_template_type {
    template <typename X>
    using type = typename _internal::_type_class_unary_template<
      std::decay_t<A>>::template type<X>;
};
}  // namespace fp::tools::instance

#endif  // FP_TOOLS_INSTANCE_H
