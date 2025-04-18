#pragma once
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp::fp.h>
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_META_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_META_H

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

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
}  // namespace __internal
using namespace __internal;

template <typename TC>
inline constexpr bool fp_is_instance =
  __type_class_instance<std::decay_t<TC>>::value > 0;

template <typename TC>
concept Instance = fp_is_instance<TC>;

template <typename TC>
inline constexpr bool fp_is_unary_instance =
  __type_class_unary_instance<std::decay_t<TC>>::value;

template <typename TC>
concept UnaryInstance = fp_is_unary_instance<TC>;

template <typename TC>
inline constexpr bool fp_is_binary_instance =
  __type_class_binary_instance<std::decay_t<TC>>::value;

template <typename TC>
concept BinaryInstance = fp_is_binary_instance<TC>;

template <typename TC>
inline constexpr std::size_t fp_get_instance_arity =
  __type_class_instance<std::decay_t<TC>>::value;

}  // namespace fp::tools::instance

namespace fp::tools::rebind {
using namespace fp::tools::instance;

namespace __internal {
    template <typename T>
    struct __rebind_instance {};

    template <template <typename> typename TC, typename A>
    struct __rebind_instance<TC<A>> {
        template <typename B>
        using type = TC<std::decay_t<B>>;
    };

    template <template <typename, typename> typename TC, typename A, typename B>
    struct __rebind_instance<TC<A, B>> {
        template <typename C, typename D>
        using type = TC<std::decay_t<C>, std::decay_t<D>>;
    };
};  // namespace __internal
using namespace __internal;

/// Transform TC<A> into TC<B>
template <typename TC, typename B>
    requires(fp_is_unary_instance<TC>)
using fp_rebind =
  typename __rebind_instance<std::decay_t<TC>>::template type<B>;

/// Transform TC<A, B> into TC<C, D>
template <typename TC, typename C, typename D>
    requires(fp_is_binary_instance<TC>)
using fp_rebind_binary =
  typename __rebind_instance<std::decay_t<TC>>::template type<C, D>;

}  // namespace fp::tools::rebind

namespace fp::tools::inner_type {

using namespace fp::tools::instance;
namespace __internal {
    template <typename T>
    struct __extract_inner_type {};

    template <template <typename> typename TC, typename A>
    struct __extract_inner_type<TC<A>> {
        using type = std::decay_t<A>;
    };
}  // namespace __internal
using namespace __internal;

/// If given TC<A>, access A
template <UnaryInstance TC>
using fp_inner_type = typename __extract_inner_type<std::decay_t<TC>>::type;

/// Given two instances, check if their inner types are the same (i.e.
/// std::optional<int> and std::vectro<double> will result in false)
template <UnaryInstance TA, UnaryInstance TB>
inline constexpr bool fp_is_same_inner_type = std::
  same_as<fp_inner_type<std::decay_t<TA>>, fp_inner_type<std::decay_t<TB>>>;

}  // namespace fp::tools::inner_type

namespace fp::tools::instance_with {

using namespace fp::tools::instance;
using namespace fp::tools::inner_type;

namespace __internal {
    template <typename TA, typename TB>
    struct __is_instance_with {
        static constexpr bool value = std::same_as<TA, fp_inner_type<TB>>;
    };
}  // namespace __internal
using namespace __internal;

template <UnaryInstance TA, UnaryInstance TB>
inline constexpr bool fp_is_instance_with =
  fp_is_unary_instance<TA>
  && fp_is_instance<TB>
  && __is_instance_with<std::decay_t<TA>, std::decay_t<TB>>::value;

template <typename TA, typename TB>
concept InstanceWith = fp_is_instance_with<TA, TB>;

}  // namespace fp::tools::instance_with

namespace fp::tools::make_pair_type {

using namespace fp::tools::instance;

template <typename T>
struct __make_pair_type {};

template <template <typename, typename> typename TC, typename A, typename B>
struct __make_pair_type<TC<A, B>> {
    using first = std::decay_t<A>;
    using second = std::decay_t<B>;
};

template <typename T>
using fp_make_pair_type = std::pair<
  typename __make_pair_type<std::decay_t<T>>::first,
  typename __make_pair_type<std::decay_t<T>>::second>;
}  // namespace fp::tools::make_pair_type

namespace fp::tools::arrow {

template <typename F, typename A>
concept Arrow = requires(F f, A a) { std::invoke(f, a); }
             && !std::is_void_v<std::invoke_result_t<F, A>>;

// 5. Extract the result type (optional helper)
template <typename F, typename A>
    requires Arrow<F, A>
using fp_arrow_result = std::invoke_result_t<F, A>;

}  // namespace fp::tools::arrow

namespace fp::tools::kleisli_arrow {

using namespace fp::tools::instance;
using namespace fp::tools::inner_type;
using namespace fp::tools::arrow;

template <typename F, typename A>
    requires Arrow<F, A>
inline constexpr bool fp_is_kleisli_arrow =
  fp_is_instance<fp_arrow_result<F, A>>;

template <typename F, typename A>
concept KleisliArrow = fp_is_kleisli_arrow<F, A>;

template <typename F, typename A>
    requires KleisliArrow<F, A>
using fp_kvalue = fp_arrow_result<F, A>;

template <typename F, typename A>
    requires KleisliArrow<F, A>
using fp_kvalue_type = fp_inner_type<fp_kvalue<F, A>>;

}  // namespace fp::tools::kleisli_arrow

namespace fp::tools {
using namespace fp::tools::instance;
using namespace fp::tools::rebind;
using namespace fp::tools::inner_type;
using namespace fp::tools::instance_with;
using namespace fp::tools::make_pair_type;
using namespace fp::tools::arrow;
using namespace fp::tools::kleisli_arrow;
}  // namespace fp::tools

#endif  // FP_META_H
