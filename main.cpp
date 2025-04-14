#include <fp/fp.h>
using namespace fp::guards::callable;
using namespace fp::guards::extract_type;
using namespace fp::guards::is_template_instance;

template <template <typename> typename TC>
inline constexpr auto pure = []<typename T>(T&& t) noexcept(
                               noexcept(TC<std::decay_t<T>>{std::forward<T>(t)})
                             )
    requires fp_is_template_instance_v<TC<T>> && fp_has_apply_v<TC<T>, T>
{ return TC<std::decay_t<T>>{std::forward<T>(t)}; };

template <typename M>
concept Monad = fp_is_template_instance_v<M> && requires {
    {
        pure<fp_extract_type_constructor<M>::template type>(
          std::declval<fp_extract_dependent_type_t<M>>()
        )
    } -> std::same_as<M>;
};

// A simple Box<T> monad
template <typename T>
struct Simple {
    T value;

    explicit Simple(T v) : value(std::move(v)) {}
};

int main() {  //
    static_assert(Monad<Simple<int>>);
    auto x = pure<Simple>(42);
    std::cout << "Type: " << typeid(x).name() << "\n";
    std::cout << "Value: " << x.value << "\n";
    return 0;
};
