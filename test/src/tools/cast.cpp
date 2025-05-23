#include <fp/tools/cast.h>
#include <gtest/gtest.h>

using namespace fp::tools::cast;

TEST(Tools_Cast, fundamental) {
    static_assert(std::is_same_v<fp_cast<int>, int>);
    static_assert(std::is_same_v<fp_cast<const int>, int>);
    static_assert(std::is_same_v<fp_cast<const int&>, int>);
}

TEST(Tools_Cast, const_qualified_types) {
    static_assert(std::is_same_v<fp_cast<const int&>, int>);
    static_assert(std::is_same_v<fp_cast<const int*>, const int*>);
    static_assert(std::is_same_v<fp_cast<int* const>, int*>);
}

TEST(Tools_Cast, pointers) {
    static_assert(std::is_same_v<fp_cast<int*>, int*>);
    static_assert(std::is_same_v<fp_cast<const int*>, const int*>);
    static_assert(
      std::is_same_v<fp_cast<std::shared_ptr<int>>, std::shared_ptr<int>>
    );
    static_assert(
      std::is_same_v<fp_cast<std::unique_ptr<int>>, std::unique_ptr<int>>
    );
}

TEST(Tools_Cast, function_pointers) {
    static_assert(std::is_same_v<fp_cast<int (*)(int)>, int (*)(int)>);
    static_assert(std::is_same_v<fp_cast<void (*)(int)>, void (*)(int)>);
}

TEST(Tools_Cast, nested_templates) {
    static_assert(
      std::is_same_v<
        fp_cast<std::map<int, const char*>>, std::map<int, const char*>>
    );
    static_assert(std::is_same_v<
                  fp_cast<std::unordered_map<int, const char*>>,
                  std::unordered_map<int, const char*>>);
}

TEST(Tools_Cast, lambdas) {
    auto lambda = [](int) { return 42; };
    static_assert(std::is_same_v<fp_cast<decltype(lambda)>, decltype(lambda)>);
}

TEST(Tools_Cast, references) {
    static_assert(std::is_same_v<fp_cast<int&>, int>);
    static_assert(std::is_same_v<fp_cast<int&&>, int>);
}

TEST(Tools_Cast, enums) {
    enum class Color { Red, Green, Blue };
    static_assert(std::is_same_v<fp_cast<Color>, Color>);
}

TEST(Tools_Cast, incomplete_types) {
    struct Foo;
    static_assert(std::is_same_v<fp_cast<Foo>, Foo>);
}

TEST(Tools_Cast, c_string) {
    static_assert(std::is_same_v<fp_cast<char*>, std::string>);
    static_assert(std::is_same_v<fp_cast<const char*>, std::string>);
}

TEST(Tools_Cast, arrays) {
    static_assert(std::is_same_v<fp_cast<int[3]>, std::vector<int>>);
    static_assert(std::is_same_v<fp_cast<const int[5]>, std::vector<int>>);
    static_assert(std::is_same_v<fp_cast<std::array<int, 4>>, std::vector<int>>
    );
}

TEST(Tools_Cast, void_and_nullptr) {
    static_assert(std::is_same_v<fp_cast<void>, fp::data::nothing::Nothing>);
    static_assert(std::is_same_v<fp_cast<nullptr_t>, fp::data::nothing::Nothing>
    );
}

TEST(Tools_Cast, optional_void) {
    static_assert(
      std::is_same_v<
        fp_cast<std::optional<void>>, std::optional<fp::data::nothing::Nothing>>
    );
}
