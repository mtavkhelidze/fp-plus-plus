#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp::fp.h>
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_META_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_META_H

#include <fp/defs.h>

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
template <typename TC>
inline constexpr bool fp_is_type_class_instance =
  __is_type_class_instance<std::decay_t<TC>>::value;

// Optional concept: checks whether type constructor extraction is possible
template <typename TC>
concept fp_has_type_class_constructor = fp_is_type_class_instance<TC>;
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

namespace fp::meta::rebind_type_constructor {
template <typename T>
struct __extract_type_constructor {
    static_assert(
      sizeof(T) != sizeof(T),  // NOLINT
      "fp_rebind_type_constructor<T>: T must be of the form TC<T>"
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
 * using Maybe = fp_rebind_type_constructor<std::optional<int>, U>;
 *
 * static_assert(std::is_same_v<Maybe<double>, std::optional<double>>);
 * \endcode
 */
template <typename TC, typename U>
using fp_rebind_type_constructor =
  typename __extract_type_constructor<TC>::template type<U>;

}  // namespace fp::meta::rebind_type_constructor

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
      fp_type_constructor_arity<T> < 1,
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
      fp_type_constructor_arity<TC<T>> >= 1,
      "fp_extract_dependent_type<T>: TC<T> must have exactly one type "
      "parameter"
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
template <typename TC>
using fp_extract_dependent_type =
  typename __extract_dependent_type<std::decay_t<TC>>::type;

}  // namespace fp::meta::extract_dependent_type

namespace fp::meta::is_wrapped_by {

using namespace fp::meta::extract_dependent_type;

template <
  template <typename> typename Outer,
  template <typename> typename Inner,
  typename Given>
struct __is_wrapped_by {
    static constexpr bool value =
      std::is_same_v<Inner<Given>, fp_extract_dependent_type<Outer<Given>>>;

    static_assert(
      value, "is_wrapped_by_given: cannot construct Outer<Inner<Given>> "
    );
};

/**
 * @brief Checks that Inner is wrapped by Outer given some type Given. I.e.
 * Outer<Inneer<Given>> is valid.
 */
template <
  template <typename> typename Outer,
  template <typename> typename Inner,
  typename Given>
constexpr bool is_wrapped_by_given =
  __is_wrapped_by<Inner, Outer, Given>::value;

/**
 * \brief Checks that Inner is wrapped by Outer. Same as
 * \ref{is_wrapped_by_given}<Oouter, Inner, fp::Nothing>.
 */
template <
  template <typename> typename Outer,
  template <typename> typename Inner>
constexpr bool is_wrapped_by = is_wrapped_by_given<Inner, Outer, fp::Nothing>;

}  // namespace fp::meta::is_wrapped_by

namespace fp::meta::make_pair_type {

using namespace fp::meta::is_type_class_instance;
using namespace fp::meta::type_constructor_arity;

template <typename T>
struct __make_pair_type {
    static_assert(
      fp_is_type_class_instance<T>,
      "fp_make_pair_type<T>: T must be an instance of a type class of form "
      "TC<A, B>)"
    );

    static_assert(
      fp_type_constructor_arity<T> == 2,
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
      fp_type_constructor_arity<TC<A, B>> >= 2,
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
using namespace fp::meta::rebind_type_constructor;
using namespace fp::meta::extract_dependent_type;

template <typename F>
concept fp_is_kleisli_arrow =
  fp_is_arrow_function<F>
  && fp_is_type_class_instance<fp_arrow_function_return_type<F>>;

template <typename F>
using fp_kleisli_result_type =
  fp_extract_dependent_type<fp_arrow_function_return_type<F>>;

template <typename F>
using fp_kleisli_monad_type_constructor = fp_rebind_type_constructor<
  fp_arrow_function_return_type<F>,
  fp_kleisli_result_type<F>>;

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
// done
using namespace fp::meta::is_type_class_unary_constructor;
// done
using namespace fp::meta::is_type_class_instance;
// done
using namespace fp::meta::type_constructor_arity;
// done
using namespace fp::meta::rebind_type_constructor;
// done
using namespace fp::meta::is_wrapped_by;
// done
using namespace fp::meta::extract_dependent_type;
using namespace fp::meta::make_pair_type;
using namespace fp::meta::arrow_function;
using namespace fp::meta::is_kleisli_arrow;
}  // namespace fp::meta

#endif  // FP_META_H
