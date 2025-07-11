#ifndef FP_TOOLS_INSTANCE_H
#define FP_TOOLS_INSTANCE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <concepts>
#include <type_traits>

namespace fp::tools::instance {
namespace __internal {
    template <typename T>
    struct __type_class_instance {
        static constexpr std::size_t value = 0;
        static_assert(
          sizeof(T) != sizeof(T),  // NOLINT
          "TC must be of the form TC<...T> (i.e.std::optional<int>)."
        );
    };
    template <template <typename...> typename TC, typename... Args>
    struct __type_class_instance<TC<Args...>> {
        static constexpr std::size_t value = sizeof...(Args);
    };

    template <typename>
    struct __type_class_unary_instance : std::false_type {
        static_assert(
          sizeof(int) != sizeof(int),  // NOLINT
          "TC must be of the form TC<A> (i.e.std::optional<int>)."
        );
    };
    template <template <typename> typename TC, typename T>
    struct __type_class_unary_instance<TC<T>> : std::true_type {};

    template <typename>
    struct __type_class_binary_instance : std::false_type {
        static_assert(
          sizeof(int) != sizeof(int),  // NOLINT
          "TC must be of the form TC<A, B> (i.e.std::ppair<int, float>)."
        );
    };
    template <template <typename, typename> typename TC, typename A, typename B>
    struct __type_class_binary_instance<TC<A, B>> : std::true_type {};

    template <typename>
    struct __type_class_unary_template;

    template <template <typename> typename TC, typename A>
    struct __type_class_unary_template<TC<A>> {
        template <typename X>
        using type = TC<X>;
    };
}  // namespace __internal

template <typename TC>
inline constexpr bool fp_is_instance =
  __internal::__type_class_instance<std::decay_t<TC>>::value > 0;

template <typename TC>
inline constexpr bool fp_is_unary_instance =
  __internal::__type_class_unary_instance<std::decay_t<TC>>::value;

template <typename TC>
concept AnyInstance = fp_is_instance<TC>;

template <typename TC>
concept UnaryInstance = fp_is_unary_instance<TC>;

template <typename TC>
inline constexpr bool fp_is_binary_instance =
  __internal::__type_class_binary_instance<std::decay_t<TC>>::value;

template <typename TC>
concept BinaryInstance = fp_is_binary_instance<TC>;

template <typename TC>
inline constexpr std::size_t fp_instance_arity =
  __internal::__type_class_instance<std::decay_t<TC>>::value;

template <typename TC>
inline constexpr bool fp_has_no_copy = !std::is_copy_constructible_v<TC>;

template <typename TC>
inline constexpr bool fp_has_no_move = !std::is_move_constructible_v<TC>;

template <typename TC, typename A>
inline constexpr bool fp_has_no_direct_constructor =
  !std::constructible_from<TC, A>;

template <typename T>
struct fp_unary_template_type {
    template <typename X>
    using type = typename __internal::__type_class_unary_template<
      std::decay_t<T>>::template type<X>;
};
}  // namespace fp::tools::instance
#endif  // FP_TOOLS_INSTANCE_H
