#include <fp/fp.h>

#include <type_traits>

template <template <typename> typename TC, typename T>
concept Monad = requires(TC<T> c) {
    { pure<TC>(std::declval<T>()) } -> std::same_as<TC<T>>;

    requires fp::guards::fp_is_unary<decltype([](T x) { return pure<TC>(x); })>;

    {
        flatMap(c, [](T x) { return pure<TC>(x); })
    } -> std::same_as<TC<T>>;
};
//
int main() {  //
    return 0;
}
