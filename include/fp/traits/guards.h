#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_GUARDS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_GUARDS_H

#include <type_traits>

namespace fp::traits::guards {

template <typename T, template <typename> typename TypeConstructor>
concept fp_constructible_from =
  std::is_constructible_v<TypeConstructor<std::decay_t<T>>, T> &&
  noexcept(TypeConstructor<std::decay_t<T>>{std::declval<T>()});

/// Checks whether a type T is an instantiation of the template TypeConstructor
/// (i.e. TypeConstructor<U>).

template <template <typename...> typename TypeConstructor, typename T>
struct _is_instance_of_impl : std::false_type {};

template <template <typename...> typename TypeConstructor, typename... Args>
struct _is_instance_of_impl<TypeConstructor, TypeConstructor<Args...>>
    : std::true_type {};

// Concept that checks whether T is an instantiation of TypeConstructor.
template <template <typename...> typename TypeConstructor, typename T>
concept fp_is_instance_of = _is_instance_of_impl<TypeConstructor, T>::value;

/// Boolean helper for is_instance_of concept.
template <template <typename...> typename TypeConstructor, typename T>
inline constexpr bool fp_is_instance_of_v =
  _is_instance_of_impl<TypeConstructor, T>::value;

}  // namespace fp::traits::guards

#endif  // FP_TRAITS_GUARDS_H
