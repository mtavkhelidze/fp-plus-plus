#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <variant>

template <typename T>
struct Box {
  private:
    std::shared_ptr<T> data;

  public:
    explicit inline Box(T&& t) :
        data(std::make_shared<T>(std::forward<T>(t))) {}

    explicit inline Box(const char* t)
        requires(std::is_constructible_v<T, const char*>)
        : data(std::make_shared<T>(t)) {}

    explicit inline Box(const T& t) : data(std::make_shared<T>(t)) {}

    // Defaulted copy and move
    Box(const Box&) = default;
    Box& operator=(const Box&) = default;
    Box(Box&&) = default;
    Box& operator=(Box&&) = default;
    const T* get() const { return static_cast<T*>(data.get()); }
};

template <typename T>
Box(T&&) -> Box<std::decay_t<T>>;

Box(const char*) -> Box<std::string>;

int main() {
    void* dp = nullptr;
    auto b1 = Box(1);
    auto b2 = Box("Hello");
    auto b3 = Box(dp);

    auto p1 = *b1.get();
    auto p2 = *b2.get();
    auto p3 = *b3.get();

    std::cout << *b3.get() << "\n";

    auto b4 = Box(std::array<int, 5>{1, 2, 3, 4, 5});
    std::cout << (b4.get())->at(0) << std::endl;  // Output: 1

    int* arr = new int[3]{10, 20, 30};
    auto b5 = Box(arr);                   // Box<int*>
    std::cout << *b5.get() << std::endl;  // Output: 10

    auto func = [](int x) { return x * 2; };
    auto b6 = Box(func);
    std::cout << (*b6.get())(5) << std::endl;  // Output: 10

    std::variant<int, double, std::string> var = "Hello";
    auto b8 = Box(var);
    std::cout << std::get<std::string>(*b8.get())
              << std::endl;  // Output: Hello

    auto b9 = Box(std::make_tuple(1, 2.5, "Tuple"));
    auto tup = *b9.get();
    std::cout << std::get<2>(tup) << std::endl;  // Output: Tuple

    auto b10 = Box(std::make_shared<int>(100));
    std::cout << *b10.get() << std::endl;  // Output: 100

    auto b11 = Box(std::make_unique<int>(200));
    std::cout << *b11.get() << std::endl;  // Output: 200

    struct NoCopy {
        NoCopy() = default;
        NoCopy(const NoCopy&) = delete;  // No copying allowed

        // Define move constructor
        NoCopy(NoCopy&& other) noexcept : value(other.value) {
            other.value = 0;  // optional: reset moved-from value
        }

        int value = 42;
    };
    auto b12 = Box(NoCopy{});
    std::cout << b12.get()->value << std::endl;  // Output: 42

    std::optional<int> opt = 123;
    auto b13 = Box(opt);
    std::cout << b13.get()->value() << std::endl;  // Output: 123

    std::function<int(int)> f = [](int x) { return x * 3; };
    auto b16 = Box(f);
    std::cout << (*b16.get())(4) << std::endl;  // Output: 12

    return 0;
}
