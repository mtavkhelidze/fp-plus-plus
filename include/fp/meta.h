#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp::fp.h>
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_META_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_META_H

#include <fp/defs.h>

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace fp::meta::is_type_class_unary_constructor {

template <template <typename> typename TC>
concept __type_constructible_with = requires { typename TC<void>; };

/**
 * @brief Checks whether TC is a unary type constructor.
 *
 * Succeeds if TC can be instantiated as TC<T> for any type T.
 *
 * Example:
 * @code
 *
 * template <typename T>
 * struct Simple {};
 *
 * static_assert(fp_is_unary_constructor<Simple>);
 * @endcode
 */
template <template <typename> typename TC>
inline constexpr bool fp_is_unary_constructor = __type_constructible_with<TC>;

template <template <typename> typename TC>
concept fp_unary_constructor = fp_is_unary_constructor<TC>;

}  // namespace fp::meta::is_type_class_unary_constructor

namespace fp::meta::is_type_class_instance {

template <typename>
struct __is_type_class_instance : std::false_type {};

// Specialization: matches any instantiation of a unary template
template <template <typename> typename TC, typename T>
struct __is_type_class_instance<TC<T>> : std::true_type {};

/**
 * @brief Concept or constant that checks whether a type T is an instance
 *        of some unary type constructor.
 *
 * @code
 * template <typename T> struct Simple {};
 * static_assert(fp_is_type_class_instance<Simple<int>>);
 * static_assert(!fp_is_type_class_instance<int>);
 * @endcode
 */
template <typename TC>
inline constexpr bool fp_is_type_class_instance =
  __is_type_class_instance<std::decay_t<TC>>::value;

template <typename TC>
concept fp_type_class_instance =
  __is_type_class_instance<std::decay_t<TC>>::value;

}  // namespace fp::meta::is_type_class_instance

namespace fp::meta::constructor_arity {

template <typename T>
struct __type_constructor_arity {
    static constexpr std::size_t value = 0;
};

template <template <typename...> typename TC, typename... Args>
struct __type_constructor_arity<TC<Args...>> {
    static constexpr std::size_t value = sizeof...(Args);
};
/**
 * @brief Returns the number of type arguments of a type constructor.
 *
 * @example
 * template <typename T>
 * using Optional = std::optional<T>;
 * static_assert(fp_get_constructor_arity<Optional<int>> == 1);
 */
template <typename T>
inline constexpr std::size_t fp_get_constructor_arity =
  __type_constructor_arity<T>::value;

}  // namespace fp::meta::constructor_arity

namespace fp::meta::rebind_constructor {
template <typename T>
struct __extract_type_constructor {
    static_assert(
      sizeof(T) != sizeof(T),  // NOLINT
      "fp_rebind_constructor<T>: T must be of the form TC<T>"
    );
};

template <template <typename...> typename TC, typename Arg>
struct __extract_type_constructor<TC<Arg>> {
    template <typename U>
    using type = TC<U>;
};

/**
 * \short Rebinds TC<T> to TC<U> where T can be any type, valid for TC and U is
 * user supplied type.
 *
 * \code(.cpp)
 * template <typename U>
 * using Maybe = fp_rebind_constructor<std::optional<int>, U>;
 *
 * static_assert(std::is_same_v<Maybe<double>, std::optional<double>>);
 * \endcode
 */
template <typename TC, typename U>
using fp_rebind_constructor =
  typename __extract_type_constructor<TC>::template type<U>;

}  // namespace fp::meta::rebind_constructor

namespace fp::meta::inner_type {

using namespace fp::meta::constructor_arity;
using namespace fp::meta::is_type_class_instance;

template <typename T>
struct __extract_inner_type {
    static_assert(
      fp_is_type_class_instance<T>,
      "fp_inner_type<T>: T must be an instance of a type class "
      "(e.g., TC<T>)"
    );

    static_assert(
      fp_get_constructor_arity<T> < 1,
      "fp_inner_type<T>: Type class instance must have arity 1 "
      "(i.e., TC<T>)"
    );

    static_assert(
      sizeof(T) != sizeof(T),  // NOLINT
      "fp_inner_type<T>: Unknown structure; T must be of the form "
      "TC<T>"
    );
};

template <template <typename> typename TC, typename T>
struct __extract_inner_type<TC<T>> {
    static_assert(
      fp_is_type_class_instance<TC<T>>,
      "fp_inner_type<T>: TC<T> is not a recognized type class "
      "instance"
    );

    static_assert(
      fp_get_constructor_arity<TC<T>> >= 1,
      "fp_inner_type<T>: TC<T> must have exactly one type "
      "parameter"
    );

    using type = T;
};

/**
 * @brief Extracts the dependent type T from a type constructor TC<T>.
 *
 * @example
 * template <typename T> struct Box {};
 * using T = fp_inner_type<Box<int>>; // int
 */
template <typename TC>
using fp_inner_type = typename __extract_inner_type<std::decay_t<TC>>::type;

template <typename T, typename TC>
concept fp_has_inner_type = requires { typename fp_inner_type<TC>; }
                         && std::same_as<fp_inner_type<TC>, T>;

template <typename TA, typename TB>
concept fp_has_same_inner_type = requires {
    typename fp_inner_type<TA>;
    typename fp_inner_type<TB>;
} && std::same_as<fp_inner_type<TA>, fp_inner_type<TB>>;
}  // namespace fp::meta::inner_type

namespace fp::meta::fp_is_wrapped_by {

using namespace fp::meta::inner_type;

template <
  template <typename> typename Outer,
  template <typename> typename Inner,
  typename Given>
struct __is_wrapped_by {
    static constexpr bool value =
      std::is_same_v<Inner<Given>, fp_inner_type<Outer<Given>>>;

    static_assert(
      value, "fp_is_wrapped_by_with: cannot construct Outer<Inner<Given>> "
    );
};

template <
  template <typename> typename Inner,
  template <typename> typename Outer,
  typename Given>
constexpr bool fp_is_wrapped_by_with =
  __is_wrapped_by<Inner, Outer, Given>::value;

template <
  template <typename> typename Inner,
  template <typename> typename Outer,
  typename Given>
concept fp_wrapped_by_with = __is_wrapped_by<Inner, Outer, Given>::value;

template <
  template <typename> typename Inner,
  template <typename> typename Outer>
constexpr bool fp_is_wrapped_by =
  fp_is_wrapped_by_with<Inner, Outer, fp::Nothing>;

template <
  template <typename> typename Inner,
  template <typename> typename Outer>
concept fp_wrapped_by = fp_is_wrapped_by_with<Inner, Outer, fp::Nothing>;

template <
  template <typename> typename Outer,
  template <typename> typename Inner,
  typename T>
concept fp_is_wrapped_as = fp_wrapped_by_with<Inner, Outer, T>;
}  // namespace fp::meta::fp_is_wrapped_by

namespace fp::meta::make_pair_type {

using namespace fp::meta::is_type_class_instance;
using namespace fp::meta::constructor_arity;

template <typename T>
struct __make_pair_type {
    static_assert(
      fp_is_type_class_instance<T>,
      "fp_make_pair_type<T>: T must be an instance of a type class of form "
      "TC<A, B>)"
    );

    static_assert(
      fp_get_constructor_arity<T> == 2,
      "fp_make_pair_type<T>: T must have exactly two type parameters (i.e., "
      "TC<A, B>)"
    );

    static_assert(
      sizeof(T) != sizeof(T),  // NOLINT
      "fp_make_pair_type<T>: Unexpected type structure"
    );
};

template <template <typename, typename> typename TC, typename A, typename B>
struct __make_pair_type<TC<A, B>> {
    static_assert(
      fp_get_constructor_arity<TC<A, B>> >= 2,
      "fp_make_pair_type<Type>: Type must be of the form TC<A, B> (with arity "
      "2)."
    );

    using first = A;
    using second = B;
};

/**
 * @brief Converts types of the form `TC<A, B>` into `std::pair<A, B>`.
 *
 * @example
 * using Map = std::map<std::string, float>;
 * using Tuple = fp_make_pair_type<Map>; // std::pair<std::string, float>
 */
template <typename T>
using fp_make_pair_type = std::pair<
  typename __make_pair_type<T>::first,
  typename __make_pair_type<T>::second>;

}  // namespace fp::meta::make_pair_type

namespace fp::meta::arrow_function {

// various function types
template <typename T>
struct __arrow_function {
    static_assert(
      sizeof(T) != sizeof(T),  // NOLINT
      "pf_is_arrow_function::__arrow_function<T>: Unsupported "
      "function type. Only single-argument functions, function pointers, or "
      "lambdas are allowed."
    );
};

// Function pointer
template <typename R, typename A>
struct __arrow_function<R (*)(A)> {
    using a = A;
    using b = R;
    static constexpr std::size_t arity = 1;
};

template <typename R, typename A>
struct __arrow_function<R(A)> {
    using a = A;
    using b = R;
    static constexpr std::size_t arity = 1;
};

// Member function pointers (lambdas, functors)
template <typename R, typename A, typename M>
struct __arrow_function<R (M::*)(A)> {
    using a = A;
    using b = R;
    static constexpr std::size_t arity = 1;
};

template <typename R, typename A, typename M>
struct __arrow_function<R (M::*)(A) const> {
    using a = A;
    using b = R;
    static constexpr std::size_t arity = 1;
};

template <typename R, typename A, typename M>
struct __arrow_function<R (M::*)(A) &> {
    using a = A;
    using b = R;
    static constexpr std::size_t arity = 1;
};

template <typename R, typename A, typename M>
struct __arrow_function<R (M::*)(A) const &> {
    using a = A;
    using b = R;
    static constexpr std::size_t arity = 1;
};

template <typename R, typename A, typename M>
struct __arrow_function<R (M::*)(A) &&> {
    using a = A;
    using b = R;
    static constexpr std::size_t arity = 1;
};

template <typename R, typename A, typename M>
struct __arrow_function<R (M::*)(A) const &&> {
    using a = A;
    using b = R;
    static constexpr std::size_t arity = 1;
};

template <typename F>
struct __arrow_traits : __arrow_function<decltype(&F::operator())> {};

// Specializations for plain function and function pointers
template <typename R, typename A>
struct __arrow_traits<R(A)> : __arrow_function<R(A)> {};

template <typename R, typename A>
struct __arrow_traits<R (*)(A)> : __arrow_function<R (*)(A)> {};

template <typename F>
using __arrow_arg = typename __arrow_traits<F>::a;

template <typename F>
using __arrow_ret = typename __arrow_traits<F>::b;

template <typename F>
constexpr std::size_t __arrow_arity = __arrow_traits<F>::arity;

// SFINAE fallback
template <typename F, typename = void>
struct __fp_is_arrow_function : std::false_type {
    static_assert(
      sizeof(F) != sizeof(F),  // NOLINT
      "arrow_function: F does not appear to be a unary  function, pointer, "
      "or lambda with exactly one argument."
    );
};

template <typename F>
struct __fp_is_arrow_function<
  F,
  std::void_t<
    decltype(std::declval<F>()(std::declval<__arrow_arg<F>>())),
    __arrow_ret<F>>> : std::true_type {};

template <typename F>
inline constexpr bool fp_is_arrow_function = __fp_is_arrow_function<F>::value;

template <typename F>
concept fp_arrow_function = fp_is_arrow_function<F>;

template <fp_arrow_function F>
using fp_get_arrow_function_argument_type = __arrow_arg<F>;

template <fp_arrow_function F>
using fp_get_arrow_function_return_type = __arrow_ret<F>;
}  // namespace fp::meta::arrow_function

namespace fp::meta::is_kleisli_arrow {

using namespace fp::meta::arrow_function;
using namespace fp::meta::is_type_class_instance;
using namespace fp::meta::rebind_constructor;
using namespace fp::meta::inner_type;

template <fp_arrow_function F>
inline constexpr bool fp_is_kleisli_arrow =
  fp_is_type_class_instance<fp_get_arrow_function_return_type<F>>;

template <typename F>
concept fp_kleisli_arrow = fp_is_kleisli_arrow<F>;

template <fp_kleisli_arrow F>
using fp_get_kleisli_result_type =
  fp_inner_type<fp_get_arrow_function_return_type<F>>;

template <fp_kleisli_arrow F>
using fp_get_kleisli_type_constructor = fp_rebind_constructor<
  fp_get_arrow_function_return_type<F>,
  fp_get_kleisli_result_type<F>>;

}  // namespace fp::meta::is_kleisli_arrow

namespace fp::meta {
using namespace fp::meta::is_type_class_unary_constructor;
using namespace fp::meta::is_type_class_instance;
using namespace fp::meta::constructor_arity;
using namespace fp::meta::rebind_constructor;
using namespace fp::meta::fp_is_wrapped_by;
using namespace fp::meta::inner_type;
using namespace fp::meta::make_pair_type;
using namespace fp::meta::arrow_function;
using namespace fp::meta::is_kleisli_arrow;
}  // namespace fp::meta

#endif  // FP_META_H
