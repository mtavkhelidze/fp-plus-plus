#include <fp/meta.h>
#include <gtest/gtest.h>

#include <optional>
#include <type_traits>
#include <vector>

template <typename T>
struct UnaryStruct {};

template <typename T, typename U>
struct BinaryStruct {};

struct NoTemplateStruct {};

// NOLINTNEXTLINE
TEST(Meta, fp_is_type_class_unary_constructor_check) {
    using namespace fp::meta::is_type_class_unary_constructor;

    static_assert(fp_is_type_class_unary_constructor<UnaryStruct>);

    // Uncommenting these should cause a compilation error
    // static_assert(!fp_is_type_class_unary_constructor<NoTemplateStruct>);
    // static_assert(!fp_is_type_class_unary_constructor<BinaryStruct>);
}

// NOLINTNEXTLINE
TEST(Meta, fp_is_type_class_instance_check) {
    using namespace fp::meta::is_type_class_instance;

    using Int = UnaryStruct<int>;
    static_assert(fp_is_type_class_instance<Int>);
    static_assert(fp_is_type_class_instance<decltype(Int{})>);

    static_assert(!fp_is_type_class_instance<NoTemplateStruct>);
    static_assert(!fp_is_type_class_instance<decltype(NoTemplateStruct{})>);

    using NumPair = BinaryStruct<int, float>;
    static_assert(!fp_is_type_class_instance<NumPair>);
    static_assert(!fp_is_type_class_instance<decltype(NumPair{})>);
}

// NOLINTNEXTLINE
TEST(Meta, fp_type_constructor_arity_check) {
    using namespace fp::meta::type_constructor_arity;

    static_assert(fp_type_constructor_arity<UnaryStruct<int>> == 1);
    static_assert(fp_type_constructor_arity<decltype(UnaryStruct<int>{})> == 1);

    static_assert(fp_type_constructor_arity<BinaryStruct<int, float>> == 2);
    static_assert(
      fp_type_constructor_arity<decltype(BinaryStruct<int, float>{})> == 2
    );

    static_assert(fp_type_constructor_arity<NoTemplateStruct> == 0);
    static_assert(fp_type_constructor_arity<decltype(NoTemplateStruct{})> == 0);
}

template <typename U>
using Maybe = fp::meta::rebind_type_constructor::
  fp_rebind_type_constructor<std::optional<int>, U>;

// NOLINTNEXTLINE
TEST(Meta, fp_rebind_type_constructor_check) {
    static_assert(std::is_same_v<Maybe<double>, std::optional<double>>);
}

// NOLINTNEXTLINE
TEST(Meta, fp_is_nested_instance_of_check) {
    using namespace fp::meta::is_wrapped_by;
    //    static_assert(fp_is_nested_instance_of<VectorOfMaybes, Maybe, int>);
}
