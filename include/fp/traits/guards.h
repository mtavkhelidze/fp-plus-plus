#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_GUARDS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_GUARDS_H

#include <type_traits>

namespace fp::traits::guards {
template <
  template <typename> typename Outer, template <typename> typename Inner,
  typename T>
struct _is_nested_instance_of_impl : std::false_type {};

template <
  template <typename> typename Outer, template <typename> typename Inner,
  typename T>
struct _is_nested_instance_of_impl<Outer, Inner, Outer<Inner<T>>>
    : std::true_type {};

template <
  template <typename> typename Outer, template <typename> typename Inner,
  typename T>
concept fp_is_nested_instance_of =
  _is_nested_instance_of_impl<Outer, Inner, T>::value;

template <typename T, template <typename> typename TC>
concept fp_constructible_from =
  std::is_constructible_v<TC<std::decay_t<T>>, T>
  && noexcept(TC<std::decay_t<T>>{std::declval<T>()});

/// Checks whether a type T is an instantiation of the template TC
/// (i.e. TC<U>).

template <template <typename...> typename TC, typename T>
struct _is_instance_of_impl : std::false_type {};

template <template <typename...> typename TC, typename... Args>
struct _is_instance_of_impl<TC, TC<Args...>> : std::true_type {};

// Concept that checks whether T is an instantiation of TC.
template <template <typename...> typename TC, typename T>
concept fp_is_instance_of = _is_instance_of_impl<TC, T>::value;

/// Boolean helper for is_instance_of concept.
template <template <typename...> typename TC, typename T>
inline constexpr bool fp_is_instance_of_v = _is_instance_of_impl<TC, T>::value;

template <typename T, template <typename...> typename... TypeConstructors>
constexpr bool fp_is_instance_of_any_v =
  (fp_is_instance_of<TypeConstructors, T> || ...);
template <typename>
struct fp_extract_type_constructor;

template <template <typename> typename TC, typename T>
struct fp_extract_type_constructor<TC<T>> {
    template <typename U>
    using type = TC<U>;
};

template <typename T>
using fp_extract_type_constructor_t =
  typename fp_extract_type_constructor<T>::type;

}  // namespace fp::traits::guards

#endif  // FP_TRAITS_GUARDS_H
