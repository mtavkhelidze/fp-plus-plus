#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp::fp.h>
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_GUARDS_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_GUARDS_H

#include <type_traits>

namespace fp::guards::is_template_instance {
/**
 * @brief Checks whether a type is an instantiation of a unary template.
 *
 * This primary template resolves to std::false_type. Specializations exist for
 * types of the form TC<T>, where TC is a template that takes a single type
 * parameter.
 *
 * @tparam T The type to inspect.
 */
template <typename T>
struct fp_is_template_instance : std::false_type {};

/**
 * @brief Specialization that returns true for unary template instantiations.
 *
 * Matches types of the form TC<T> where TC is a unary template and T is any
 * type.
 *
 * @tparam TC The unary template.
 * @tparam T The type parameter applied to TC.
 */
template <template <typename> typename TC, typename T>
struct fp_is_template_instance<TC<T>> : std::true_type {};

/**
 * @brief Convenience variable template for fp_is_template_instance.
 *
 * Resolves to true if the type is an instantiation of a unary template.
 *
 * @tparam T The type to inspect.
 */
template <typename T>
inline constexpr bool fp_is_template_instance_v =
  fp_is_template_instance<T>::value;

}  // namespace fp::guards::is_template_instance

namespace fp::guards::extract_type_constructor {
/**
 * @brief Extracts the type constructor from a unary template instance.
 *
 * Only enabled if the input type T is an instantiation of a unary template.
 *
 * @tparam T The type from which to extract the constructor.
 */
template <
  typename T,
  typename = std::enable_if_t<
    fp::guards::is_template_instance::fp_is_template_instance<T>::value>>
struct fp_extract_type_constructor;

/**
 * @brief Specialization that captures the template TC from TC<T>.
 *
 * Defines a nested alias `type<U>` which rebinds TC to another type U.
 *
 * @tparam TC The unary template.
 * @tparam T The original applied type.
 */
template <template <typename> typename TC, typename T>
struct fp_extract_type_constructor<TC<T>> {
    template <typename U>
    using type = TC<U>;
};

/**
 * @brief Rebinds a unary type constructor to a different type.
 *
 * Given an instantiation like TC<T>, this extracts TC and applies it to U.
 *
 * @tparam T A type of the form TC<X>, from which the constructor TC will be
 * extracted.
 * @tparam U The type to apply the constructor to.
 */
template <typename T, typename U>
using fp_rebind_type_t =
  typename fp_extract_type_constructor<T>::template type<U>;
}  // namespace fp::guards::extract_type_constructor

namespace fp::guards::is_nested_instance_of {
template <
  template <typename> typename Outer, template <typename> typename Inner,
  typename T>
struct _is_nested_instance_of_impl : std::false_type {};

template <
  template <typename> typename Outer, template <typename> typename Inner,
  typename T>
struct _is_nested_instance_of_impl<Outer, Inner, Outer<Inner<T>>>
    : std::true_type {};

/**
 * @brief Concept that checks whether a type T is an instance of
 * Outer<Inner<T>>.
 *
 * @tparam Outer The outer unary template.
 * @tparam Inner The inner unary template.
 * @tparam T The type to check.
 */
template <
  template <typename> typename Outer, template <typename> typename Inner,
  typename T>
concept fp_is_nested_instance_of =
  _is_nested_instance_of_impl<Outer, Inner, T>::value;

}  // namespace fp::guards::is_nested_instance_of

namespace fp::guards::callable {
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

// Lambda or functor - mutable
template <typename C, typename Ret, typename Arg>
struct fp_callable_arg<Ret (C::*)(Arg)> {
    using type = Arg;
};

// Lambda or functor - const &
template <typename C, typename Ret, typename Arg>
struct fp_callable_arg<Ret (C::*)(Arg) const &> {
    using type = Arg;
};

// Lambda or functor - mutable &
template <typename C, typename Ret, typename Arg>
struct fp_callable_arg<Ret (C::*)(Arg) &> {
    using type = Arg;
};

// Lambda or functor - const &&
template <typename C, typename Ret, typename Arg>
struct fp_callable_arg<Ret (C::*)(Arg) const &&> {
    using type = Arg;
};

// Lambda or functor - mutable &&
template <typename C, typename Ret, typename Arg>
struct fp_callable_arg<Ret (C::*)(Arg) &&> {
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
struct _fp_is_unary {
  private:
    template <typename U>
    static auto test(int)
      -> decltype(std::declval<U>()(std::declval<_fp_unary_arg_selector<U>::type>()), std::true_type{});

    template <typename>
    static std::false_type test(...);

  public:
    static constexpr bool value = decltype(test<F>(0))::value;
};

/**
 * @brief Concept that checks whether a callable takes exactly one argument.
 *
 * Supports function pointers, plain function types, lambdas, and functors with
 * a unary operator().
 *
 * @tparam F The callable type to check.
 */
template <typename F>
concept fp_is_unary = _fp_is_unary<F>::value;

/**
 * @brief Extracts the return type of a unary callable.
 *
 * Given a callable type F that takes a single argument, this metafunction
 * deduces the type of the result of invoking F with its unary argument type.
 *
 * @tparam F The callable type.
 */
template <typename F>
using fp_unary_arg_t = typename _fp_unary_arg_selector<F>::type;

template <typename F>
struct fp_callable_result {
    using type = decltype(std::declval<F>()(std::declval<fp_unary_arg_t<F>>()));
};

/**
 * @brief Alias for the return type of a unary callable.
 *
 * Convenience alias for fp_callable_result<F>::type.
 *
 * @tparam F The callable type.
 */
template <typename F>
using fp_result_t = typename fp_callable_result<F>::type;
}  // namespace fp::guards::callable

namespace fp::guards {
using namespace fp::guards::callable;
using namespace fp::guards::is_nested_instance_of;
using namespace fp::guards::is_template_instance;
using namespace fp::guards::extract_type_constructor;
}  // namespace fp::guards

#endif  // FP_GUARDS_H
