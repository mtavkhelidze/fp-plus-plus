#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp::prelude;
using namespace fp::core;
using namespace fp::internal::storage::box;

template <typename T>
constexpr void check_fp_cast_vs_box() {
    static_assert(
      std::is_same_v<fp_cast<T>, typename Box<std::decay_t<T>>::kind>,
      "fp_cast and Box::kind mismatch"
    );
}

TEST(Tools_Cast, fp_cast_vs_box_int) { check_fp_cast_vs_box<int>(); }

TEST(Tools_Cast, fp_cast_vs_box_const_int) {
    check_fp_cast_vs_box<const int>();
}

TEST(Tools_Cast, fp_cast_vs_box_char_pointer) { check_fp_cast_vs_box<char*>(); }

TEST(Tools_Cast, fp_cast_vs_box_const_char_pointer) {
    check_fp_cast_vs_box<const char*>();
}

TEST(Tools_Cast, fp_cast_vs_box_int_array) { check_fp_cast_vs_box<int[3]>(); }

TEST(Tools_Cast, fp_cast_vs_box_std_array) {
    check_fp_cast_vs_box<std::array<int, 4>>();
}

TEST(Tools_Cast, fp_cast_vs_box_shared_ptr) {
    check_fp_cast_vs_box<std::shared_ptr<int>>();
}

TEST(Tools_Cast, fp_cast_vs_box_unique_ptr) {
    check_fp_cast_vs_box<std::unique_ptr<int>>();
}

TEST(Tools_Cast, fp_cast_vs_box_std_string) {
    check_fp_cast_vs_box<std::string>();
}

TEST(Tools_Cast, fp_cast_vs_box_tuple_mixed) {
    check_fp_cast_vs_box<
      std::tuple<int, const char*, std::unique_ptr<double>>>();
}

TEST(Tools_Cast, fp_cast_vs_box_optional_void) {
    check_fp_cast_vs_box<std::optional<void>>();
}

TEST(Tools_Cast, fp_cast_vs_box_std_function) {
    check_fp_cast_vs_box<std::function<int(int)>>();
}

TEST(Tools_Cast, fp_cast_vs_box_map_with_pointer) {
    check_fp_cast_vs_box<std::map<std::string, const char*>>();
}

TEST(Tools_Cast, fp_cast_vs_box_lambda_type) {
    auto lam = [](int x) { return x * 2; };
    check_fp_cast_vs_box<decltype(lam)>();
}

TEST(Tools_Cast, fp_cast_vs_box_nullptr_t) {
    check_fp_cast_vs_box<std::nullptr_t>();
}

TEST(Tools_Cast, fp_cast_vs_box_reference_wrapper) {
    check_fp_cast_vs_box<std::reference_wrapper<int>>();
}

struct Incomplete;
TEST(Tools_Cast, fp_cast_vs_box_incomplete_type) {
    check_fp_cast_vs_box<Incomplete>();
}
