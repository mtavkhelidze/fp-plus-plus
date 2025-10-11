#include <iostream>
#include <string_view>

template <typename T>
constexpr auto class_name() -> std::string_view {
#if defined(__clang__) || defined(__GNUC__)
    constexpr std::string_view func = __PRETTY_FUNCTION__;
    constexpr std::string_view prefix = "T = ";
    constexpr std::string_view suffix = "]";
#elif defined(_MSC_VER)
    constexpr std::string_view func = __FUNCSIG__;
    constexpr std::string_view prefix = "class_name<";
    constexpr std::string_view suffix = ">(void)";
#endif
    const auto start = func.find(prefix) + prefix.size();
    const auto end = func.find(suffix, start);
    return func.substr(start, end - start);
}

struct FooMisha {
    void print() const { std::cout << class_name<decltype(*this)>() << '\n'; }
};

int main() { FooMisha{}.print(); }
