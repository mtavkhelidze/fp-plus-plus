#include <fp/fp.h>

#include <iostream>

using namespace fp;

auto main() -> int {
    auto b101 = Box(1, 2, 3);
    std::cout << "b101: " << typeid(b101).name() << " : " << (*b101.get())[0]
              << "\n";

    auto b100 = Box(Box(Box(142)));  // Box<int>
    std::cout << "b100: " << typeid(b100).name() << " : " << *b100.get()
              << "\n";

    auto b1 = Box(1);
    std::cout << "b1: " << typeid(b1).name() << " : " << *b1.get() << "\n";

    std::string h = "hello", w = "world";
    auto b2a = Box("hello");
    auto b2b = Box(1, 2, 3);
    auto b2c = Box(&h, &w);
    std::cout << "b2a: " << typeid(b2a).name() << " : value : " << *b2a.get()
              << "\n";
    std::cout << "b2b: " << typeid(b2b).name() << " : value : " << b2b.get()[1]
              << "\n";
    std::cout << "b2c: " << typeid(b2c).name() << " : value : " << *b2c.get()[1]
              << "\n";

    void* dp = nullptr;
    Box<void*> b3 = Box(dp);
    auto dpa = nullptr;
    auto b3a = Box(dpa);
    //    std::cout << "b3: " << typeid(b3).name() << " : " << *b3.get() <<
    //    "\n";

    int x = 10;
    auto arr = &x;
    auto b5 = Box(arr);
    std::cout << "b5: " << typeid(b5).name() << " : " << *b5.get() << "'n";

    auto func = [](int x) { return x * 2; };
    auto b6 = Box(func);
    std::cout << "b6: " << typeid(b6).name() << " : " << b6.get()(5) << "'n";

    std::variant<int, double, std::string> var = "Hello";
    auto b8 = Box(var);
    std::cout << "b8: " << typeid(b8).name() << " : " << b8.get().index()
              << "'n";

    auto b9 = Box(std::make_tuple(1, 2.5, "Tuple"));
    auto tup = b9.get();
    std::cout << "b9: " << typeid(b9).name() << " : " << std::get<2>(tup)
              << "'n";

    auto b10 = Box(std::make_shared<int>(100));
    std::cout << "b10: " << typeid(b10).name() << " : " << *b10.get() << "'n";

    auto b11 = Box(std::make_unique<int>(200));
    std::cout << "b11: " << typeid(b11).name() << " : " << *b11.get() << "'n";

    struct NoCopy {
        NoCopy() = default;
        NoCopy(const NoCopy&) = delete;

        NoCopy(NoCopy&& other) noexcept : value(other.value) {
            other.value = 0;
        }

        int value = 42;
    };
    auto b12 = Box(NoCopy{});
    std::cout << "b12: " << typeid(b12).name() << " : " << b12.get().value
              << "'n";

    std::optional<int> opt = 123;
    auto b13 = Box(opt);
    std::cout << "b13: " << typeid(b13).name() << " : " << *b13.get() << "'n";

    std::function<int(int)> f = [](int x) { return x * 3; };
    auto b16 = Box(f);
    std::cout << "b16: " << typeid(b16).name() << " : " << b16.get()(4) << "'n";

    return 0;
}
