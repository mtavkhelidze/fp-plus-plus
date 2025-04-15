#include <fp/fp.h>
// using namespace fp::guards::callable;
using namespace fp::meta::is_type_class_instance;

template <template <typename> typename TC>
inline constexpr auto pure = []<typename T>(T&& t) noexcept(
                               noexcept(TC<std::decay_t<T>>{std::forward<T>(t)})
                             )
    requires fp_is_type_class_instance<TC<T>>
{ return TC<std::decay_t<T>>{std::forward<T>(t)}; };

// template <typename M>
// concept fp_has_pure = fp_is_template_instance_v<M> && requires {
//     {
//         pure<fp_extract_type_constructor<M>::template type>(
//           std::declval<fp_extract_dependent_type_t<M>>()
//         )
//     } -> std::same_as<M>;
// };

// template <typename F, typename M>
// concept fp_is_kleisli_arrow = fp_is_template_instance<M> && []() {
//     using inner_t = fp_extract_dependent_type_t<M>;
//     using result_t = std::invoke_result_t<F, inner_t>;
//     return fp_is_callable_with_v<F, inner_t>
//         && fp_is_template_instance_v<result_t>
//         && std::same_as<
//              fp_extract_type_constructor<M>,
//              fp_extract_type_constructor<result_t>>;
// }();

// template <typename M>
// constexpr bool fp_has_flatMap() {
//     using Inner = fp_extract_dependent_type_t<M>;
//     auto arrow = [](auto x) { return M(x); };
//     using Kleisli = decltype(arrow);

//     if constexpr (fp_is_kleisli_arrow<Kleisli, M>) {
//         bool r = requires(M m) {
//             {
//                 m.flatMap(arrow)
//             } -> std::same_as<decltype(arrow(std::declval<Inner>()))>;
//         };
//         return r;
//     } else {
//         return false;
//     }
// }

// template <typename M>
// concept Monad = fp_has_pure<M> && fp_has_flatMap<M>();

template <typename T>
struct Simple {
    T value;

    explicit Simple(T v) : value(std::move(v)) {}

    template <typename F>
    // requires fp_is_kleisli_arrow<F, T, Simple>
    auto flatMap(F&& f) const {
        return std::invoke(std::forward<F>(f), value);
    }
};

template <typename T>
struct NotSoSimple {
    T value;

    explicit NotSoSimple(T v) : value(std::move(v)) {}
};

// static_assert(Monad<Simple<int>>, "Nope");

int main() {  //
    auto arrow = [](int x) { return pure<Simple>(std::to_string(x) + "!"); };
    // static_assert(fp_is_kleisli_arrow<decltype(arrow), int, Simple>, "Nope");
    // auto r = pure<Simple>(42).flatMap(arrow);
    // std::cout << r.value << std::endl;
    return 0;
}
