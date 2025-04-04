#include <fp/fp.h>

#include <array>
#include <iostream>
#include <vector>

using namespace fp;

int add(int x, int y) { return x + y; }

int main() {
    int a = 42;
    char str[] = "hello";
    char* ptr = str;
    int* int_ptr = &a;
    const int* const_ptr = &a;
    int* null_p = nullptr;

    std::array<int, 3> arr = {1, 2, 3};
    std::vector<int> vec = {4, 5, 6};

    // Function pointer
    int (*fn_ptr)(int, int) = &add;

    auto o1 = Some(ptr);      // char*
    auto o2 = Some(int_ptr);  // int*
    auto o3 = Some(arr);      // std::array<int, 3>
    auto o4 = Some(vec);      // std::vector<int>
    auto o5 = Some(fn_ptr);   // int(*)(int, int)
    auto o6 = Some(const_ptr);
    auto o7 = Some(null_p);  // int

    static_assert(std::is_same_v<decltype(o1), Option<char*>>);
    static_assert(std::is_same_v<decltype(o2), Option<int*>>);
    static_assert(std::is_same_v<decltype(o3), Option<std::array<int, 3>>>);
    static_assert(std::is_same_v<decltype(o4), Option<std::vector<int>>>);
    static_assert(std::is_same_v<decltype(o5), Option<int (*)(int, int)>>);
    static_assert(std::is_same_v<decltype(o6), Option<const int*>>);
    static_assert(std::is_same_v<decltype(o7), Option<int*>>);

    return 0;
}
