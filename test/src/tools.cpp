// #include <fp/meta.h>
// #include <gtest/gtest.h>

// #include <functional>
// #include <map>
// #include <optional>
// #include <string>
// #include <type_traits>
// #include <utility>
// #include <vector>

// template <typename T>
// struct UnaryStruct {};

// template <typename T, typename U>
// struct BinaryStruct {};

// struct NoTemplateStruct {};

// // NOLINTNEXTLINE
// TEST(Meta, fp_is_type_class_unary_constructor_check) {
//     using namespace fp::tools::type_class_unary_constructor;

//     static_assert(fp_is_unary_constructor<UnaryStruct>);

//     // Uncommenting these should cause a compilation error
//     // static_assert(!fp_is_unary_constructor<NoTemplateStruct>);
//     // static_assert(!fp_is_unary_constructor<BinaryStruct>);
// }

// // NOLINTNEXTLINE
// TEST(Meta, fp_arrow_function_check) {
//     using namespace fp::tools::arrow_function;

//     constexpr double double_number = 1.5;

//     auto lambda = [](int x) -> double { return x + double_number; };
//     using Lambda = decltype(lambda);

//     static_assert(fp_is_arrow_function<Lambda>);
//     static_assert(
//       std::is_same_v<fp_get_arrow_function_argument_type<Lambda>, int>
//     );
//     static_assert(
//       std::is_same_v<fp_get_arrow_function_return_type<Lambda>, double>
//     );

//     double (*func_ptr)(int) = [](int x) { return static_cast<double>(x); };
//     using FuncPtr = decltype(func_ptr);

//     static_assert(fp_is_arrow_function<FuncPtr>);
//     static_assert(
//       std::is_same_v<fp_get_arrow_function_argument_type<FuncPtr>, int>
//     );
//     static_assert(
//       std::is_same_v<fp_get_arrow_function_return_type<FuncPtr>, double>
//     );

//     struct Callable {
//         auto operator()(int x) const -> double { return x + double_number; }
//     };

//     static_assert(fp_is_arrow_function<Callable>);
//     static_assert(
//       std::is_same_v<fp_get_arrow_function_argument_type<Callable>, int>
//     );
//     static_assert(
//       std::is_same_v<fp_get_arrow_function_return_type<Callable>, double>
//     );

//     // static_assert(fp_is_arrow_function<std::identity>);

//     // Uncommenting this should cause a compilation error
//     //    struct BadFunctor { double operator()(int, int) const; };
//     //    static_assert(fp_is_arrow_function<BadFunctor>);
// }

// // NOLINTNEXTLINE
// TEST(Meta, fp_is_type_class_instance_check) {
//     using namespace fp::tools::type_class_instance;

//     using Int = UnaryStruct<int>;
//     static_assert(fp_is_type_class_instance<Int>);
//     static_assert(fp_is_type_class_instance<decltype(Int{})>);

//     static_assert(!fp_is_type_class_instance<NoTemplateStruct>);
//     static_assert(!fp_is_type_class_instance<decltype(NoTemplateStruct{})>);

//     using NumPair = BinaryStruct<int, float>;
//     static_assert(!fp_is_type_class_instance<NumPair>);
//     static_assert(!fp_is_type_class_instance<decltype(NumPair{})>);
// }

// // NOLINTNEXTLINE
// TEST(Meta, fp_type_constructor_arity_check) {
//     using namespace fp::tools::constructor_arity;

//     static_assert(fp_get_constructor_arity<UnaryStruct<int>> == 1);
//     static_assert(fp_get_constructor_arity<decltype(UnaryStruct<int>{})> ==
//     1);

//     static_assert(fp_get_constructor_arity<BinaryStruct<int, float>> == 2);
//     static_assert(
//       fp_get_constructor_arity<decltype(BinaryStruct<int, float>{})> == 2
//     );

//     static_assert(fp_get_constructor_arity<NoTemplateStruct> == 0);
//     static_assert(fp_get_constructor_arity<decltype(NoTemplateStruct{})> ==
//     0);
// }

// template <typename U>
// using Maybe =
//   fp::tools::rebind_constructor::fp_rebind_constructor<std::optional<int>,
//   U>;

// // NOLINTNEXTLINE
// TEST(Meta, fp_rebind_constructor_check) {
//     using namespace fp::tools::rebind_constructor;
//     using Orig = std::optional<int>;
//     using Rebound = fp_rebind_constructor<Orig, double>;
//     static_assert(std::is_same_v<Rebound, std::optional<double>>);
// }

// template <typename T>
// using Vector = std::vector<Maybe<T>>;

// // NOLINTNEXTLINE
// TEST(Meta, fp_is_nested_instance_of_check) {
//     using namespace fp::tools::is_wrapped_by;
//     static_assert(fp_is_wrapped_by<Vector, Maybe>);
// }

// // NOLINTNEXTLINE
// TEST(Meta, fp_extract_dependent_type_check) {
//     using namespace fp::tools::inner_type;

//     using Extracted = fp_inner_type<UnaryStruct<int>>;
//     static_assert(std::is_same_v<Extracted, int>);

//     using Boxed = fp_inner_type<UnaryStruct<UnaryStruct<int>>>;
//     static_assert(std::is_same_v<Boxed, UnaryStruct<int>>);

//     using ExtractedConst = fp_inner_type<const UnaryStruct<int>>;
//     static_assert(std::is_same_v<ExtractedConst, int>);

//     // Uncommenting this should cause a compilation error
//     //    using FailExtract = fp_inner_type<NoTemplateStruct>;
// }

// // NOLINTNEXTLINE
// TEST(Meta, fp_make_pair_type_check) {
//     using namespace fp::tools::make_pair_type;

//     using Map = std::map<std::string, float>;
//     using ResultOne = fp_make_pair_type<Map>;

//     static_assert(std::is_same_v<ResultOne, std::pair<std::string, float>>);

//     using JustPair = std::pair<int, double>;
//     using PairWithPair = std::pair<JustPair, char>;
//     using ResultTwo = fp_make_pair_type<PairWithPair>;

//     static_assert(std::is_same_v<ResultTwo, std::pair<JustPair, char>>);

//     // Uncommenting these should cause a compilation error
//     //    using Invalid = fp_make_pair_type<int>;
// }

// // NOLINTNEXTLINE
// TEST(Meta, fp_is_kleisli_arrow_check) {
//     using namespace fp::tools::kleisli_arrow;

//     auto kleisli = [](int x) -> std::optional<double> {
//         return x > 0 ? std::optional<double>{static_cast<double>(x)}
//                      : std::nullopt;
//     };

//     using Kleisli = decltype(kleisli);

//     static_assert(fp_is_kleisli_arrow<Kleisli>);
//     static_assert(std::is_same_v<fp_get_kleisli_result_type<Kleisli>,
//     double>); static_assert(
//       std::is_same_v<
//         fp_get_kleisli_type_constructor<Kleisli>, std::optional<double>>
//     );

//     auto nonKleisli = [](int x) -> double { return static_cast<double>(x); };

//     using NonKleisli = decltype(nonKleisli);

//     static_assert(!fp_is_kleisli_arrow<NonKleisli>);
// }
