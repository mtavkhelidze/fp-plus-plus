#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_TRAITS_GUARDS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_TRAITS_GUARDS_H

#include <type_traits>

namespace fp::traits::guards::is_unary {
// Helper to extract argument type from various function types
template <typename T>
struct fp_callable_arg;

// Function pointer
template <typename Ret, typename Arg>
struct fp_callable_arg<Ret (*)(Arg)> {
    using type = Arg;
};
// Plain function type
template <typename Ret, typename Arg>
struct fp_callable_arg<Ret(Arg)> {
    using type = Arg;
};

// Lambda or functor
template <typename C, typename Ret, typename Arg>
struct fp_callable_arg<Ret (C::*)(Arg) const> {
    using type = Arg;
};

template <typename F>
struct _fp_unary_arg_selector {
    using type = typename fp_callable_arg<decltype(&F::operator())>::type;
};

template <typename Ret, typename Arg>
struct _fp_unary_arg_selector<Ret(Arg)> {
    using type = typename fp_callable_arg<Ret(Arg)>::type;
};

template <typename Ret, typename Arg>
struct _fp_unary_arg_selector<Ret (*)(Arg)> {
    using type = typename fp_callable_arg<Ret (*)(Arg)>::type;
};

template <typename F>
using fp_unary_arg_t = typename _fp_unary_arg_selector<F>::type;

template <typename F>
struct _fp_is_unary {
  private:
    template <typename U>
    static auto test(int)
      -> decltype(std::declval<U>()(std::declval<fp_unary_arg_t<U>>()), std::true_type{});

    template <typename>
    static std::false_type test(...);

  public:
    static constexpr bool value = decltype(test<F>(0))::value;
};

template <typename F>
concept fp_is_unary = _fp_is_unary<F>::value;

}  // namespace fp::traits::guards::is_unary

namespace fp::traits::guards::constructible_from {
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

}  // namespace fp::traits::guards::constructible_from

namespace fp::traits::guards::is_instance_of {

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

}  // namespace fp::traits::guards::is_instance_of

namespace fp::traits::guards::extract_type_constructor {

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

}  // namespace fp::traits::guards::extract_type_constructor

namespace fp::traits::guards {
using namespace fp::traits::guards::is_unary;
using namespace fp::traits::guards::constructible_from;
using namespace fp::traits::guards::is_instance_of;
using namespace fp::traits::guards::extract_type_constructor;
}  // namespace fp::traits::guards

#endif  // FP_TRAITS_GUARDS_H
