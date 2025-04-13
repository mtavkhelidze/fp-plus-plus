
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_GUARDS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_GUARDS_H

#include <type_traits>

namespace fp::traits::guards {
// Base template: fallback to false
template <template <typename...> typename Container, typename T>
struct is_instance_of_impl : std::false_type {};

// Specialization: if T == Container<Args...>, return true
template <template <typename...> typename Container, typename... Args>
struct is_instance_of_impl<Container, Container<Args...>> : std::true_type {};

// Final concept
template <template <typename...> typename Container, typename T>
concept is_instance_of = is_instance_of_impl<Container, T>::value;
}  // namespace fp::traits::guards

#endif  // FP_TRAITS_GUARDS_H
