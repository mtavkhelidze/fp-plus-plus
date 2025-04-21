#include <fp/fp.h>

#include <iostream>
#include <type_traits>
#include <utility>

namespace func {
using namespace fp::tools::instance;

template <template <typename> typename FA, typename A>
    requires(UnaryInstance<FA<A>>)
constexpr auto pure(A&& a) -> FA<std::decay_t<A>> {
    return FA<std::decay_t<A>>::apply(std::forward<A>(a));
}
}  // namespace func

template <template <typename> typename TC, typename A>
struct BoxedStorage {
    template <typename T>
    using Derived = fp::tools::rebind::fp_rebind<TC<A>, T>;
    using Box = fp::internal::box::Box<A>;

  private:
    Box box;

  protected:
    // 1. Default constructor
    explicit BoxedStorage() : box() {}

    // 2. Constructor from value
    explicit BoxedStorage(const A& value) : box(value) {}

    // 3. Copy constructor
    BoxedStorage(const BoxedStorage& other)
        : box([&]() {
            auto* ptr = other.box.getOrNull();
            return ptr ? Box(*ptr) : Box();
        }()) {}

    // 4. Move constructor
    BoxedStorage(BoxedStorage&& other) noexcept : box(std::move(other.box)) {}

  public:
    template <typename T>
    static auto store(T&& value) -> Derived<std::decay_t<T>> {  //
        return Derived<std::decay_t<T>>{std::forward<T>(value)};
    }

    auto getOrElse(const A& alt) const -> A {
#ifdef FP_PLUS_PLUS_TESTING
        if (auto* ptr = box.getOrNull()) {
            std::cout << "Boxed value: " << *ptr << std::endl;
        }
#endif
        auto* ptr = box.getOrNull();
        return ptr == nullptr ? alt : *ptr;
    }
};

template <template <typename> typename TC, typename A>
    requires std::is_fundamental_v<A>
struct StackStorage {
  private:
    A value;

  public:
    StackStorage(A a) : value(a) {}

  public:
    template <typename T>
    static auto store(T&& x) -> TC<std::decay_t<T>> {  //
        return TC(std::forward<std::decay_t<T>>(x));
    };

    auto getOrElse(const A&) const -> A {  //
#ifdef FP_PLUS_PLUS_TESTING
        std::cout << "Simple value: " << value << std::endl;
#endif
        return value;
    }
};

template <template <typename> typename TC, typename A>
struct Storage {
    using type = BoxedStorage<TC, A>;
};

template <template <typename> typename TC, typename A>
    requires(std::is_fundamental_v<A>)
struct Storage<TC, A> {
    using type = StackStorage<TC, A>;
};

template <typename T>
struct StorageProxy : public Storage<StorageProxy, T>::type {
  private:
    using Storage = typename Storage<StorageProxy, T>::type;
    friend Storage;

  public:
    using Storage::Storage;
};

template <typename A>
struct Mono : public StorageProxy<A> {
  private:
    using Storage = StorageProxy<A>::template BoxedStorage<Mono, A>;
};

// namespace {
// using fp::tools::inner_type::fp_inner_type;
// using fp::tools::instance::fp_is_binary_instance;

// template <typename ST, typename TC>
// concept StorageBase = requires(ST st, fp_inner_type<TC> a) {
//     { TC::template store<fp_inner_type<TC>>(a) } -> std::same_as<TC>;
//     { st.getOrElse(a) } -> std::same_as<fp_inner_type<TC>>;
// };
// static_assert(StorageBase<BoxedStorage<Mono, std::string>,
// Mono<std::string>>); }  // namespace
struct Int : public StorageProxy<int> {
  private:
    using Storage = typename StorageProxy<int>::StackStorage;

  public:
    // auto operator=(int x) -> Int {  //
    //     return Int(x);
    // }
    // auto operator=(const int& x) -> Int {  //
    //     return Int(std::decay_t<int>(x));
    // }
    // auto operator+(const int& x) const -> Int {  //
    //     return Int(this->getOrElse(0) + x);
    // }
};

auto main() -> int {
    int fortyTwo = 42;
    std::string str = "Hello, World!";

    Int x = Int(fortyTwo);
    auto y = Mono<std::string>::store(str);

    std::cout << "x: " << x.getOrElse(0) << std::endl;
    std::cout << "t: " << y.getOrElse("") << std::endl;
    return 0;
}
