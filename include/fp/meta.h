#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp::fp.h>
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_META_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_META_H

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
 * static_assert(fp_is_type_class_unary_constructor<Simple>);
 * @endcode
 */
template <template <typename> typename TC>
inline constexpr bool fp_is_type_class_unary_constructor =
  __type_constructible_with<TC>;

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
template <typename T>
inline constexpr bool fp_is_type_class_instance =
  __is_type_class_instance<T>::value;

// Optional concept: checks whether type constructor extraction is possible
template <typename T>
concept fp_has_type_class_constructor = fp_is_type_class_instance<T>;
}  // namespace fp::meta::is_type_class_instance

namespace fp::meta::type_constructor_arity {

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
 * static_assert(fp_type_constructor_arity<Optional<int>> == 1);
 */
template <typename T>
inline constexpr std::size_t fp_type_constructor_arity =
  __type_constructor_arity<T>::value;

}  // namespace fp::meta::type_constructor_arity

namespace fp::meta::extract_type_constructor {

using namespace fp::meta::type_constructor_arity;

template <typename T>
struct __extract_type_constructor {
    static_assert(
      sizeof(T) != sizeof(T),  // NOLINT
      "fp_extract_type_constructor<T>: T must be of the form TC<...>"
    );
};

template <template <typename...> typename TC, typename... Args>
struct __extract_type_constructor<TC<Args...>> {
    template <typename... Us>
    using rebind = TC<Us...>;

    // optional, can be useful somewhere
    using type = TC<Args...>;
};

/**
 * @brief Extracts the type constructor from a type of the form TC<Args...>.
 *
 * @example
 *
 * template <typename T>
 * using Optional = std::optional<T>;
 *
 * using Extracted = fp_extract_type_constructor<Optional<int>>;
 * static_assert(std::is_same_v<Extracted<double>, Optional<double>>);
 */
template <typename T>
using fp_extract_type_constructor =
  typename __extract_type_constructor<T>::rebind;

/**
 * @brief Extracts unary type constructor from a type of the form TC<Arg>.
 *
 * See \ref fp_extract_type_constructor for more details.
 *
 * @tparam T A type with one type argument, like std::vector<int>.
 */
template <typename T>
using fp_extract_type_constructor_unary = std::enable_if_t<
  fp_type_constructor_arity<T> == 1, fp_extract_type_constructor<T>>;

/**
 * @brief Extracts a binary type constructor from a type of the form TC<Arg1,
 * Arg2>.
 *
 * See @ref fp_extract_type_constructor for more details.
 *
 * @tparam T A type with two type arguments, like std::pair<int, float>.
 */
template <typename T>
using fp_extract_type_constructor_binary = std::enable_if_t<
  fp_type_constructor_arity<T> == 2, fp_extract_type_constructor<T>>;
}  // namespace fp::meta::extract_type_constructor

namespace fp::meta::is_nested_instance_of {

template <
  template <typename> typename Outer, template <typename> typename Inner,
  typename T>
struct __is_nested_instance_of : std::false_type {};

template <
  template <typename> typename Outer, template <typename> typename Inner,
  typename T>
struct __is_nested_instance_of<Outer, Inner, Outer<Inner<T>>>
    : std::true_type {};

/**
 * @brief Concept that checks whether a type T is an instance of
 * Outer<Inner<T>>.
 *
 * @example
 * template <typename T> using Box = std::optional<T>;
 * template <typename T> using Wrapper = std::vector<T>;
 * static_assert(fp_is_nested_instance_of<Wrapper, Box, Wrapper<Box<int>>>);
 * static_assert(!fp_is_nested_instance_of<Wrapper, Box, Box<Wrapper<int>>>);
 */
template <
  template <typename> typename Outer, template <typename> typename Inner,
  typename T>
concept fp_is_nested_instance_of =
  __is_nested_instance_of<Outer, Inner, T>::value;

}  // namespace fp::meta::is_nested_instance_of

namespace fp::meta::extract_dependent_type {

using namespace fp::meta::type_constructor_arity;
using namespace fp::meta::is_type_class_instance;

template <typename T>
struct __extract_dependent_type {
    static_assert(
      fp_is_type_class_instance<T>,
      "fp_extract_dependent_type<T>: T must be an instance of a type class "
      "(e.g., TC<T>)"
    );

    static_assert(
      fp_type_constructor_arity<T> == 1,
      "fp_extract_dependent_type<T>: Type class instance must have arity 1 "
      "(i.e., TC<T>)"
    );

    static_assert(
      sizeof(T) != sizeof(T),  // NOLINT
      "fp_extract_dependent_type<T>: Unknown structure; T must be of the form "
      "TC<T>"
    );
};

template <template <typename> typename TC, typename T>
struct __extract_dependent_type<TC<T>> {
    static_assert(
      fp_is_type_class_instance<TC<T>>,
      "fp_extract_dependent_type<T>: TC<T> is not a recognized type class "
      "instance"
    );

    static_assert(
      fp_type_constructor_arity<TC<T>> == 1,
      "fp_extract_dependent_type<T>: TC<T> must have exactly one type parameter"
    );

    using type = T;
};

/**
 * @brief Extracts the dependent type T from a type constructor TC<T>.
 *
 * @example
 * template <typename T> struct Box {};
 * using T = fp_extract_dependent_type<Box<int>>; // int
 */
template <typename T>
using fp_extract_dependent_type = typename __extract_dependent_type<T>::type;

}  // namespace fp::meta::extract_dependent_type

namespace fp::meta::make_pair_type {

using namespace fp::meta::is_type_class_instance;
using namespace fp::meta::type_constructor_arity;

template <typename T>
struct __make_tuple_type {
    static_assert(
      fp_is_type_class_instance<T>,
      "fp_make_tuple_type<T>: T must be an instance of a type class of form "
      "TC<A, B>)"
    );

    static_assert(
      fp_type_constructor_arity<T> == 2,
      "fp_make_tuple_type<T>: T must have exactly two type parameters (i.e., "
      "TC<A, B>)"
    );

    static_assert(
      sizeof(T) != sizeof(T),  // NOLINT
      "fp_make_tuple_type<T>: Unexpected type structure"
    );
};

template <template <typename, typename> typename TC, typename A, typename B>
struct __make_tuple_type<TC<A, B>> {
    static_assert(
      fp_type_constructor_arity<TC<A, B>> == 2,
      "fp_make_tuple_type<T>: T must be of the form TC<A, B> (with arity 2)."
    );

    using first = A;
    using second = B;
};

/**
 * @brief Converts types of the form `TC<A, B>` into `std::pair<A, B>`.
 *
 * @example
 * using Map = std::map<std::string, float>;
 * using Tuple = fp_make_tuple_type<Map>; // std::pair<std::string, float>
 */
template <typename T>
using fp_make_tuple_type = std::pair<
  typename __make_tuple_type<T>::first, typename __make_tuple_type<T>::second>;

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
  F, std::void_t<
       decltype(std::declval<F>()(std::declval<__arrow_arg<F>>())),
       __arrow_ret<F>>> : std::true_type {};

/**
 * Checks whether a type F is a unary function, pointer, or lambda with exactly
 * one argument.
 */
template <typename F>
concept fp_is_arrow_function = __fp_is_arrow_function<F>::value;

template <typename F>
using fp_arrow_function_argument_type =
  std::enable_if_t<fp_is_arrow_function<F>, __arrow_arg<F>>;

template <typename F>
using fp_arrow_function_return_type =
  std::enable_if_t<fp_is_arrow_function<F>, __arrow_ret<F>>;

}  // namespace fp::meta::arrow_function

namespace fp::meta::is_kleisli_arrow {

using namespace fp::meta::arrow_function;
using namespace fp::meta::is_type_class_instance;
using namespace fp::meta::extract_type_constructor;
using namespace fp::meta::extract_dependent_type;

template <typename F>
concept fp_is_kleisli_arrow =
  fp_is_arrow_function<F>
  && fp_is_type_class_instance<fp_arrow_function_return_type<F>>;

template <typename F>
using fp_kleisli_monad_type_constructor =
  fp_extract_type_constructor<fp_arrow_function_return_type<F>>;

template <typename F>
using fp_kleisli_result_type =
  fp_extract_dependent_type<fp_arrow_function_return_type<F>>;
}  // namespace fp::meta::is_kleisli_arrow

namespace fp::meta::callable {

// template <typename F>
// struct fp_callable_result {
//     using type =
//     decltype(std::declval<F>()(std::declval<fp_unary_arg_t<F>>()));
// };

// /**
//  * @brief Alias for the return type of a unary callable.
//  *
//  * Convenience alias for fp_callable_result<F>::type.
//  *
//  * @param F The callable type.
//  */
// template <typename F>
// using fp_callable_result_t = typename fp_callable_result<F>::type;

// template <typename F, typename Arg, typename = void>
// struct fp_is_callable_with : std::false_type {};

// template <typename F, typename Arg>
// struct fp_is_callable_with<
//   F, Arg, std::void_t<decltype(std::declval<F>()(std::declval<Arg>()))>>
//     : std::true_type {};

// template <typename F, typename Arg>
// inline constexpr bool fp_is_callable_with_v =
//   fp_is_callable_with<F, Arg>::value;

}  // namespace fp::meta::callable

namespace fp::meta {
using namespace fp::meta::is_type_class_unary_constructor;
using namespace fp::meta::is_type_class_instance;
using namespace fp::meta::type_constructor_arity;
using namespace fp::meta::extract_type_constructor;
using namespace fp::meta::is_nested_instance_of;
using namespace fp::meta::extract_dependent_type;
using namespace fp::meta::make_pair_type;
using namespace fp::meta::arrow_function;
using namespace fp::meta::is_kleisli_arrow;
}  // namespace fp::meta

#endif  // FP_META_H
