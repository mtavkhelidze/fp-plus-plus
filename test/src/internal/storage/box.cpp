/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <functional>
#include <memory>
#include <tuple>
#include <type_traits>

// NOLINTBEGIN(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

using ::testing::Test;
using namespace fp;
using namespace fp::internal::storage;

TEST(Box_Copy, constructor_behavior) {
    Box<String> a = Box("hello");
    const Box<String> b(a);  // NOLINT
    ASSERT_EQ(a.get(), b.get());
}

TEST(Box_Copy, semantics) {
    auto a = Box<int>(42);
    const auto& b = a;
    ASSERT_EQ(a.get(), b.get());
}

TEST(Box_Copy, shared_reference_count_behavior) {
    auto shared = std::make_shared<int>(99);
    auto a = Box(shared);
    const auto b = a;  // NOLINT
    ASSERT_EQ(&a.get(), &b.get());
}

TEST(Box_Construction, callable_lambda_expression) {
    // lambda expression
    auto lambda = []() { return 42; };
    auto box = Box(lambda);
    static_assert(
      std::is_same_v<decltype(lambda), typename decltype(box)::kind>
    );

    auto f = box.get();
    ASSERT_EQ(f(), 42);
}

TEST(Box_Construction, callable_std_function) {
    std::function<int(int)> const func = [](int x) { return x * 2; };
    auto box = Box(func);
    static_assert(
      std::is_same_v<std::function<int(int)>, typename decltype(box)::kind>
    );

    auto f = box.get();
    ASSERT_EQ(f(5), 10);
}

TEST(Box_Construction, function_pointer) {
    // function pointer
    using FuncType = int (*)(int);
    FuncType func = [](int x) { return x * 2; };
    auto box = Box(func);
    static_assert(std::is_same_v<FuncType, typename decltype(box)::kind>);

    auto f = box.get();
    ASSERT_EQ(f(5), 10);
}

TEST(Box_Construction, literal_c_arrays) {
    int arr1[] = {1, 2, 3};  // NOLINT
    auto box1 = Box(arr1);
    static_assert(std::is_same_v<Vector<int>, typename decltype(box1)::kind>);

    auto v1 = box1.get();
    static_assert(std::is_same_v<Vector<int>, decltype(v1)>);
    ASSERT_EQ(v1[0], 1);
    ASSERT_EQ(v1[1], 2);
    ASSERT_EQ(v1[2], 3);

    String arr2[] = {"one", "two", "three"};  // NOLINT
    auto box2 = Box(arr2);
    static_assert(
      std::is_same_v<Vector<String>, typename decltype(box2)::kind>
    );

    auto v2 = box2.get();
    static_assert(std::is_same_v<Vector<String>, decltype(v2)>);
    ASSERT_EQ(v2[0], "one");
    ASSERT_EQ(v2[1], "two");
    ASSERT_EQ(v2[2], "three");
}

TEST(Box_Construction, literal_fundamental) {
    auto box1 = Box<int>(1);
    static_assert(std::is_same_v<int, typename decltype(box1)::kind>);
    ASSERT_EQ(box1.get(), 1);

    const double x = 1.0;
    auto box2 = Box(x);
    static_assert(std::is_same_v<double, typename decltype(box2)::kind>);
    ASSERT_EQ(box2.get(), 1);

    // Implicit conversion from double to int for testing type resolution
    const int& y = x;  // NOLINT
    auto box3 = Box(y);
    static_assert(std::is_same_v<int, typename decltype(box3)::kind>);
    ASSERT_EQ(box3.get(), 1);
}

TEST(Box_Construction, literal_string) {
    Box box1("hello");
    static_assert(std::is_same_v<String, typename decltype(box1)::kind>);
    ASSERT_EQ(box1.get(), "hello");

    const auto* str = "hello";
    auto& str_ref = str;
    auto box2 = Box(str_ref);
    static_assert(std::is_same_v<Box<String>, decltype(box2)>);
    ASSERT_EQ(box2.get(), "hello");
}

TEST(Box_Construction, move_only_rvalue_and_smart_ptr) {
    // move-only type and rvalue move-only smart pointer
    struct MoveOnly {  // NOLINT
        MoveOnly() = default;
        MoveOnly(MoveOnly&&) = default;
        MoveOnly(const MoveOnly&) = delete;
        ~MoveOnly() = default;
    };
    auto box1 = Box<MoveOnly>(MoveOnly{});
    static_assert(std::is_same_v<MoveOnly, typename decltype(box1)::kind>);

    auto box2 = Box<std::unique_ptr<int>>{std::make_unique<int>(5)};
    static_assert(
      std::is_same_v<std::unique_ptr<int>, typename decltype(box2)::kind>
    );
}

TEST(Box_Construction, nothing_and_nullptr_distinction) {
    // Box<int>() — no value, but type is int
    Box<int> empty_box;
    static_assert(std::is_same_v<int, typename decltype(empty_box)::kind>);
    ASSERT_TRUE(empty_box.empty());

    // Box<int*>(nullptr) — has value, value is null pointer
    Box<int*> null_ptr_box(nullptr);
    static_assert(std::is_same_v<int*, typename decltype(null_ptr_box)::kind>);
    ASSERT_FALSE(null_ptr_box.empty());
    ASSERT_EQ(null_ptr_box.get(), nullptr);

    // Test explicit Box<std::nullptr_t>(nullptr)
    auto explicit_null_box = Box<std::nullptr_t>(nullptr);
    static_assert(
      std::is_same_v<std::nullptr_t, typename decltype(explicit_null_box)::kind>
    );
    ASSERT_FALSE(
      explicit_null_box.empty()
    );  // A Box<nullptr_t> is not "empty" in the Nothing sense
    ASSERT_EQ(explicit_null_box.get(), nullptr);

    // Test Box with a null shared_ptr
    std::shared_ptr<int> null_int_ptr = nullptr;
    auto box_null_shared_ptr = Box<std::shared_ptr<int>>(null_int_ptr);
    static_assert(
      std::is_same_v<
        std::shared_ptr<int>, typename decltype(box_null_shared_ptr)::kind>
    );
    ASSERT_FALSE(box_null_shared_ptr.empty());  // A Box<shared_ptr<int>> is not
                                                // "empty" in the Nothing sense
    ASSERT_EQ(
      box_null_shared_ptr.get(),
      nullptr
    );  // The contained shared_ptr is null
}

TEST(Box_Construction, object_copy_only_type) {
    // copy-only type
    struct CopyOnly {  // NOLINT
        CopyOnly() = default;
        CopyOnly(const CopyOnly&) = default;
        CopyOnly(CopyOnly&&) = delete;
    };
    auto box = Box<CopyOnly>(CopyOnly{});
    static_assert(std::is_same_v<CopyOnly, typename decltype(box)::kind>);
}

TEST(Box_Construction, pure_pointer) {
    auto sp = std::make_shared<int>(42);  // keep shared_ptr alive
    int* x = sp.get();
    auto box = Box(x);
    int* v = box.get();
    ASSERT_EQ(*v, 42);
}

TEST(Box_Construction, reference_collapsing_behavior) {
    int x = 42;
    int& ref = x;
    int&& rref = 42;

    auto box1 = Box(ref);
    static_assert(std::is_same_v<Box<int>, decltype(box1)>);

    auto box2 = Box<int>(rref);
    static_assert(std::is_same_v<Box<int>, decltype(box2)>);
}

TEST(Box_Construction, shared_ptr) {
    // shared_ptr and rvalue shared_ptr
    auto ptr = std::make_shared<String>("hello");
    auto box1 = Box(ptr);
    static_assert(std::is_same_v<String, typename decltype(box1)::kind>);

    struct MyType {};
    auto box2 = Box(std::make_shared<MyType>());
    static_assert(std::is_same_v<MyType, typename decltype(box2)::kind>);
}

TEST(Box_Construction, unique_ptr_transfer) {
    auto ptr = std::make_unique<int>(42);
    auto box = Box(ptr);  // ptr is drained here
    static_assert(std::is_same_v<int, typename decltype(box)::kind>);
    ASSERT_EQ(box.get(), 42);
    ASSERT_EQ(ptr, nullptr);  // ownership transferred
}

TEST(Box_Construction, unique_ptr_rvalue_deduction) {
    // rvalue unique_ptr<T> → Box<unique_ptr<T>>, move-only constructor named
    // unique_ptr<T> → Box<T>, ownership transferred via lvalue ref constructor
    auto box_of_uptr = Box(std::make_unique<int>(42));
    static_assert(
      std::is_same_v<std::unique_ptr<int>, typename decltype(box_of_uptr)::kind>
    );

    // Named unique_ptr → Box<T> as expected
    auto ptr = std::make_unique<int>(42);
    auto box_of_int = Box(ptr);
    static_assert(std::is_same_v<int, typename decltype(box_of_int)::kind>);
    ASSERT_EQ(box_of_int.get(), 42);
    ASSERT_EQ(ptr, nullptr);
}

TEST(Box_Construction, unit_type) {
    auto box = Box(whatever);
    static_assert(std::is_same_v<Unit, typename decltype(box)::kind>);
    EXPECT_EQ(box.get(), whatever);
}

TEST(Box_Extra, immutability) {
    static_assert(
      std::is_const_v<std::remove_reference_t<decltype(Box<int>(1).get())>>
    );
}

TEST(Box_Construction_Tuple, nested_recuriseve_tuple) {
    auto x = Tuple("const char*", 10);
    auto y = Tuple(x, 'c');
    auto box = Box(y);
    static_assert(
      std::is_same_v<
        Tuple<Tuple<String, int>, char>, typename decltype(box)::kind>
    );
    auto t = box.get();
    static_assert(std::is_same_v<Tuple<Tuple<String, int>, char>, decltype(t)>);

    // inner tuple
    auto inner = std::get<0>(t);
    ASSERT_EQ(std::get<0>(inner), String("const char*"));
    ASSERT_EQ(std::get<1>(inner), 10);

    // outer tuple
    ASSERT_EQ(std::get<1>(t), 'c');
}

TEST(Box_Construction_Tuple, empty_tuple) {
    // Box<> deduces to Tuple<>
    auto box = Box(Tuple<>{});
    static_assert(std::is_same_v<Tuple<>, typename decltype(box)::kind>);
    auto t = box.get();
    static_assert(std::is_same_v<Tuple<>, decltype(t)>);
    ASSERT_EQ(std::tuple_size<decltype(t)>::value, 0);
}

TEST(Box_Construction_Tuple, single_type_tuple) {
    const int x = 10;
    const int y = 20;
    auto box = Box(Tuple{x, y});
    static_assert(
      std::is_same_v<Tuple<int, int>, typename decltype(box)::kind>
    );
    auto t = box.get();
    static_assert(std::is_same_v<Tuple<int, int>, decltype(t)>);
    ASSERT_EQ(std::get<0>(t), x);
    ASSERT_EQ(std::get<1>(t), y);
}

TEST(Box_Construction_Tuple, primitive_and_complex_type_tuple) {
    const int x = 10;
    const auto* const y = "const to const*";
    const auto z = String("const string");
    auto box = Box(Tuple{x, y, z});
    static_assert(
      std::is_same_v<Tuple<int, String, String>, typename decltype(box)::kind>
    );
    auto t = box.get();
    static_assert(std::is_same_v<Tuple<int, String, String>, decltype(t)>);
    ASSERT_EQ(std::get<0>(t), x);
    ASSERT_EQ(std::get<1>(t), y);
    ASSERT_EQ(std::get<2>(t), z);
}

TEST(Box_Construction_Tuple, fairly_exotic_types) {
    auto x = 42;
    auto y = String("just str");
    double z[2] = {1.0, 2.0};  // NOLINT
    auto w = {10, 20};
    auto box = Box(Tuple{x, y, z, w});
    static_assert(
      std::is_same_v<
        Tuple<int, String, double*, Vector<int>>, typename decltype(box)::kind>
    );
    auto t = box.get();
    static_assert(
      std::is_same_v<Tuple<int, String, double*, Vector<int>>, decltype(t)>
    );
    ASSERT_EQ(std::get<0>(t), x);
    ASSERT_EQ(std::get<1>(t), y);
    ASSERT_EQ(std::get<2>(t), z);
    Vector<int> W = {10, 20};
    ASSERT_EQ(std::get<3>(t), W);
}

template <typename T>
struct UserStruct {
    int x;
    T y;
};

TEST(Box_Construction_Tuple, references_and_user_types) {
    auto x = 42;
    auto& xref = x;
    auto y = UserStruct<String>{.x = 10, .y = "hello"};
    auto box = Box(x, xref, y);
    static_assert(
      std::is_same_v<
        Tuple<int, int, UserStruct<String>>, typename decltype(box)::kind>
    );
    auto t = box.get();
    static_assert(
      std::is_same_v<Tuple<int, int, UserStruct<String>>, decltype(t)>
    );
    ASSERT_EQ(std::get<0>(t), x);
    ASSERT_EQ(std::get<1>(t), x);
    ASSERT_EQ(std::get<2>(t).x, 10);
    ASSERT_EQ(std::get<2>(t).y, "hello");
}

TEST(Box_Extra, large_c_array_to_vector) {
    constexpr size_t N = 1000;
    int arr[N];  // NOLINT
#pragma unroll 10
    for (size_t i = 0; i < N; ++i) {
        arr[i] = static_cast<int>(i * i);  // NOLINT
    }
    auto box = Box(arr);
    static_assert(std::is_same_v<Vector<int>, typename decltype(box)::kind>);
    auto v = box.get();
    ASSERT_EQ(v.size(), N);
#pragma unroll 10
    for (size_t i = 0; i < N; ++i) {
        ASSERT_EQ(v[i], static_cast<int>(i * i));
    }
}

TEST(Box_Extra, nested_box) {
    auto inner = Box<int>(123);
    auto outer = Box(inner);
    static_assert(std::is_same_v<int, typename decltype(outer)::kind>);
    auto inner2 = outer.get();
    static_assert(std::is_same_v<int, decltype(inner2)>);
    ASSERT_EQ(inner2, 123);
}
// NOLINTEND(misc-non-private-member-variables-in-classes,readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
