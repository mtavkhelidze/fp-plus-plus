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

namespace fp::meta::type_class_unary_constructor {

template <template <typename> typename TC>
concept __type_constructible_with = requires { typename TC<void>; };

/**
 * @brief Checks whether TC is a unary type constructor.
 *
 * A unary type constructor is a template that takes exactly one type parameter.
 * This concept is useful for ensuring that a type constructor can be
 * instantiated with a single type argument, which is a common pattern in
 * type-level programming.
 *
 * Example:
 * @code
 *
 * template <typename T>
 * struct Simple {};
 *
 * static_assert(fp_is_unary_constructor<Simple>);
 * // Here, Simple is a unary type constructor since it takes one type
 * parameter.
 * @endcode
 */
template <template <typename> typename TC>
inline constexpr bool fp_is_unary_constructor = __type_constructible_with<TC>;

template <template <typename> typename TC>
concept fp_unary_constructor = fp_is_unary_constructor<TC>;

}  // namespace fp::meta::type_class_unary_constructor

namespace fp::meta::type_class_instance {

template <typename>
struct __is_type_class_instance : std::false_type {};

// Specialization: matches any instantiation of a unary template
template <template <typename> typename TC, typename T>
struct __is_type_class_instance<TC<T>> : std::true_type {};

/**
 * @brief Concept or constant that checks whether a type T is an instance
 *        of some unary type constructor.
 *
 * This trait is particularly useful for verifying that a type is a valid
 * instance of a type constructor that expects a single type argument. This is
 * essential in generic programming where type safety and correctness are
 * paramount.
 *
 * Example:
 * @code
 * template <typename T> struct Simple {};
 * static_assert(fp_is_type_class_instance<Simple<int>>); // Valid instance
 * static_assert(!fp_is_type_class_instance<int>); // int is not a type
 * constructor
 * @endcode
 */
template <typename TC>
inline constexpr bool fp_is_type_class_instance =
  __is_type_class_instance<std::decay_t<TC>>::value;

template <typename TC>
concept fp_type_class_instance =
  __is_type_class_instance<std::decay_t<TC>>::value;

}  // namespace fp::meta::type_class_instance

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
 * @brief Returns the number of type arguments of a type constructor instance.
 *
 * This trait is useful for inspecting instantiated types to determine how
 * many type parameters were provided. It is essential in metaprogramming
 * tasks where generic arity inspection is needed for validation or
 * transformation.
 *
 * @example
 * template <typename T, typename U>
 * struct Pair {};
 * static_assert(fp_get_constructor_arity<Pair<int, float>> == 2); // Valid
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
      "fp_rebind_constructor<T>: T must be of the form TC<T>. Example: "
      "std::optional<int>"
    );
};

template <template <typename...> typename TC, typename Arg>
struct __extract_type_constructor<TC<Arg>> {
    template <typename U>
    using type = TC<U>;
};
/**
 * @brief Rebinds a unary type constructor instance to a new type.
 *
 * This metafunction transforms a type like `TC<A>` into `TC<B>`, preserving
 * the structure of the original constructor while substituting the type
 * argument. It is useful for manipulating higher-kinded types generically.
 *
 * @example
 * using Orig = std::optional<int>;
 * using Rebound = fp_rebind_constructor<Orig, double>;
 * static_assert(std::is_same_v<Rebound, std::optional<double>>);
 */
template <typename TC, typename U>
using fp_rebind_constructor =
  typename __extract_type_constructor<TC>::template type<U>;

}  // namespace fp::meta::rebind_constructor

namespace fp::meta::inner_type {

using namespace fp::meta::constructor_arity;
using namespace fp::meta::type_class_instance;

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
      "fp_inner_type<T>: Unsupported structure; T must match the form TC<T>. "
      "Example: std::optional<int>"
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
 * This trait is useful for retrieving the type that a type constructor wraps.
 * For example, given a type like `std::optional<T>`, it allows you to extract
 * the inner type `T`. This is essential in scenarios where you need to work
 * with the type contained within a wrapper.
 *
 * @example
 * template <typename T> struct Box {};
 * using T = fp_inner_type<Box<int>>; // int
 * using InnerType = fp_inner_type<std::optional<float>>; // float
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

namespace fp::meta::is_wrapped_by {

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
inline constexpr bool fp_is_wrapped_by_with =
  __is_wrapped_by<Inner, Outer, Given>::value;

template <
  template <typename> typename Inner,
  template <typename> typename Outer,
  typename Given>
inline constexpr bool fp_wrapped_by_with_concept =
  __is_wrapped_by<Inner, Outer, Given>::value;
// Using the inline variable above to define the concept
template <
  template <typename> typename Inner,
  template <typename> typename Outer,
  typename Given>
concept fp_wrapped_by_with = fp_wrapped_by_with_concept<Inner, Outer, Given>;

template <
  template <typename> typename Inner,
  template <typename> typename Outer>
inline constexpr bool fp_is_wrapped_by =
  fp_is_wrapped_by_with<Inner, Outer, fp::Nothing>;

template <
  template <typename> typename Inner,
  template <typename> typename Outer>
inline constexpr bool fp_wrapped_by_concept =
  fp_is_wrapped_by_with<Inner, Outer, fp::Nothing>;
// Using the inline variable above to define the concept
template <
  template <typename> typename Inner,
  template <typename> typename Outer>
concept fp_wrapped_by = fp_wrapped_by_concept<Inner, Outer>;
/**
 * @brief Checks if a type is equivalent to `Outer<Inner<T>>`.
 *
 * This trait is useful for verifying deep wrapping relationships,
 * e.g., ensuring a value is wrapped first by one type constructor
 * and then another, in a specific nesting order.
 *
 * @example
 * using Wrapped = std::optional<std::vector<int>>;
 * static_assert(fp_is_wrapped_as<std::optional, std::vector, int>); // Valid
 */
template <
  template <typename> typename Outer,
  template <typename> typename Inner,
  typename T>
concept fp_is_wrapped_as = fp_wrapped_by_with<Inner, Outer, T>;

}  // namespace fp::meta::is_wrapped_by
namespace fp::meta::make_pair_type {

using namespace fp::meta::type_class_instance;
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
      "fp_make_pair_type<T>: Type must be of the form TC<A, B>. Example: "
      "std::map<std::string, float>"
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
      "fp_is_arrow_function<T>: T must be a function pointer, function type, "
      "or lambda with exactly one argument"
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
inline constexpr std::size_t __arrow_arity = __arrow_traits<F>::arity;

// SFINAE fallback
template <typename F, typename = void>
struct __fp_is_arrow_function : std::false_type {
    static_assert(
      sizeof(F) != sizeof(F),  // NOLINT
      "fp_is_arrow_function<F>: F must be a unary function, function pointer, "
      "or lambda (i.e., F(A) -> B)"
    );
};

template <typename F>
struct __fp_is_arrow_function<
  F,
  std::void_t<
    decltype(std::declval<F>()(std::declval<__arrow_arg<F>>())),
    __arrow_ret<F>>> : std::true_type {};

/**
 * @brief Checks if a function or lambda is a unary function.
 *
 * This concept verifies that a given function type takes exactly one argument
 * and returns a value. It's particularly useful in generic programming where
 * you want to ensure that a function adheres to a specific signature, allowing
 * for safer and more predictable behavior.
 *
 * @example
 * void func(int);
 * static_assert(fp_is_arrow_function<decltype(func)>); // Valid
 * auto lambda = [](double x) { return x * 2; };
 * static_assert(fp_is_arrow_function<decltype(lambda)>); // Valid
 * static_assert(!fp_is_arrow_function<void()>); // Invalid: no arguments
 * static_assert(!fp_is_arrow_function<int(int, int)>); // Invalid: multiple
 * arguments
 */
template <typename F>
inline constexpr bool fp_is_arrow_function = __fp_is_arrow_function<F>::value;

template <typename F>
concept fp_arrow_function = fp_is_arrow_function<F>;

template <fp_arrow_function F>
using fp_get_arrow_function_argument_type = __arrow_arg<F>;

template <fp_arrow_function F>
using fp_get_arrow_function_return_type = __arrow_ret<F>;
}  // namespace fp::meta::arrow_function

namespace fp::meta::kleisli_arrow {

using namespace fp::meta::arrow_function;
using namespace fp::meta::type_class_instance;
using namespace fp::meta::rebind_constructor;
using namespace fp::meta::inner_type;

/**
 * @brief Checks if a function is a Kleisli arrow.
 *
 * A Kleisli arrow is a special kind of function that returns a type wrapped
 * by a type constructor. This is useful for ensuring that a function fits
 * within the Kleisli monad framework.
 *
 * @example
 * auto kleisli_func = [](int x) { return std::optional<int>(x * 2); };
 * static_assert(fp_is_kleisli_arrow<decltype(kleisli_func)>); // Valid
 * static_assert(!fp_is_kleisli_arrow<decltype(func)>); // Invalid
 */
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

}  // namespace fp::meta::kleisli_arrow

namespace fp::meta {
using namespace fp::meta::type_class_unary_constructor;
using namespace fp::meta::type_class_instance;
using namespace fp::meta::constructor_arity;
using namespace fp::meta::rebind_constructor;
using namespace fp::meta::is_wrapped_by;
using namespace fp::meta::inner_type;
using namespace fp::meta::make_pair_type;
using namespace fp::meta::arrow_function;
using namespace fp::meta::kleisli_arrow;
}  // namespace fp::meta

#endif  // FP_META_H
