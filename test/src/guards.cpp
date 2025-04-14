#include <fp/fp.h>
#include <gtest/gtest.h>

#include <type_traits>

TEST(UnaryArgType, extractsArgumentType) {
    using namespace fp::guards::callable;

    auto lambda = [](double) { return 1.0; };
    static_assert(
      std::is_same_v<fp_unary_arg_t<decltype(lambda)>, double>,
      "Lambda should have double as argument type"
    );

    struct Functor {
        int operator()(std::string) const { return 0; }
    };
    static_assert(
      std::is_same_v<fp_unary_arg_t<Functor>, std::string>,
      "Functor should have std::string as argument type"
    );

    using FuncPtr = char (*)(bool);
    static_assert(
      std::is_same_v<fp_unary_arg_t<FuncPtr>, bool>,
      "Function pointer should have bool as argument type"
    );

    using PlainFunc = void(char);
    static_assert(
      std::is_same_v<fp_unary_arg_t<PlainFunc>, char>,
      "Plain function type should have char as argument type"
    );
}

// -----

template <typename T>
struct Wrapper {
    explicit Wrapper(T)
        requires(!std::is_same_v<T, std::nullptr_t>)
    {}
};

template <typename T>
struct Inner {};

template <typename T>
struct Outer {};

template <typename T>
struct WithTemplate {};

struct WithoutATemplate {};

TEST(IsNestedInstanceOf, works) {
    using namespace fp::guards::is_nested_instance_of;
    using Nested = Outer<Inner<int>>;
    using Flat = Outer<int>;

    static_assert(
      fp_is_nested_instance_of<Outer, Inner, Nested>,
      "Should detect Outer<Inner<T>>"
    );
    static_assert(
      !fp_is_nested_instance_of<Outer, Inner, Flat>,
      "Should not detect Outer<T>"
    );
}

TEST(IsTemplateInstance, works) {
    using namespace fp::guards::is_template_instance;

    static_assert(
      fp_is_template_instance_v<std::vector<int>>,
      "std::vector<int> should be detected as a template instance"
    );
    static_assert(
      !fp_is_template_instance_v<int>,
      "int should not be detected as a template instance"
    );

    static_assert(
      fp_is_template_instance_v<WithTemplate<double>>,
      "WithTemplate<double> should be detected as a template instance"
    );

    static_assert(
      !fp_is_template_instance_v<WithoutATemplate>,
      "Plain struct should not be detected as a template instance"
    );
}

TEST(ExtractTypeConstructor, works) {
    using namespace fp::guards::extract_type_constructor;

    using VInt = std::vector<int>;
    using VFloat = std::vector<float>;

    using Extracted = fp_rebind_type_t<VInt, float>;
    static_assert(
      std::is_same_v<Extracted, VFloat>, "Should extract std::vector<_>"
    );
}

TEST(UnaryResultType, extractsReturnType) {
    using namespace fp::guards::callable;

    auto lambda = [](int x) -> double { return x + 0.5; };
    static_assert(
      std::is_same_v<fp_result_t<decltype(lambda)>, double>,
      "Lambda should return double"
    );

    struct Functor {
        std::string operator()(bool) const { return "true"; }
    };
    static_assert(
      std::is_same_v<fp_result_t<Functor>, std::string>,
      "Functor should return std::string"
    );

    using FuncPtr = char (*)(float);
    static_assert(
      std::is_same_v<fp_result_t<FuncPtr>, char>,
      "Function pointer should return char"
    );

    using PlainFunc = int(double);
    static_assert(
      std::is_same_v<fp_result_t<PlainFunc>, int>,
      "Plain function type should return int"
    );
}
