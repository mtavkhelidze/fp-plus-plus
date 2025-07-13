#include <fp/core/all.h>
#include <fp/internal/storage/storage_box.h>
#include <gtest/gtest.h>

#include <string>
#include <type_traits>

using namespace fp::internal::storage;
using namespace fp::core;

template <typename A>
struct TestStruct : StorageBox<TestStruct<A>> {
    using Base = StorageBox<TestStruct<A>>;
    using Base::Base;

    static auto store(auto&& x) -> auto {
        return StorageBox<TestStruct<A>>::put(std::forward<decltype(x)>(x));
    }

    auto value() const { return this->get(); }
    auto has_value() const { return !this->empty(); }
};

TEST(StorageBox, const_accessors) {
    auto box = TestStruct<std::string>::store(std::string("const test"));
    const auto& const_box = box;
    EXPECT_EQ(const_box.value(), "const test");
    EXPECT_TRUE(const_box.has_value());
}

TEST(StorageBox, copy_assignment_is_shallow) {
    auto a = TestStruct<std::string>::store(std::string("foo"));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto ap = (unsigned long)(a.value().c_str());
#pragma clang diagnostic pop

    TestStruct<std::string> b =
      TestStruct<std::string>::store(std::string("bar"));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto bp = (unsigned long)(b.value().c_str());
#pragma clang diagnostic pop

    b = a;  // copy assignment

    EXPECT_TRUE(b.has_value());
    EXPECT_EQ(b.value(), a.value());
    EXPECT_EQ(bp, ap);
}

TEST(StorageBox, copy_box) {
    auto a = TestStruct<std::string>::store(std::string("hello"));
    auto b = a;

    EXPECT_TRUE(b.has_value());
    EXPECT_EQ(a.value(), b.value());
    EXPECT_NE(a.value().c_str(), b.value().c_str());
}

TEST(StorageBox, default_constructor_deleted) {
    // Can't compile, but test with static_assert
    static_assert(
      !std::is_default_constructible_v<StorageBox<TestStruct<int>>>
    );
}

TEST(StorageBox, doesnt_allow_move) {
    static_assert(
      !std::is_move_constructible_v<StorageBox<TestStruct<int>>>,
      "StorageBox should not be move constructible"
    );
    static_assert(
      !std::is_move_assignable_v<StorageBox<TestStruct<int>>>,
      "StorageBox should not be move assignable"
    );
}

TEST(StorageBox, empty_box_behavior) {
    auto box = TestStruct<Nothing>::store(nothing);
    ASSERT_TRUE(box.has_value());
}

TEST(StorageBox, multiple_copies_are_distinct) {
    auto a = TestStruct<std::string>::store(std::string("copytest"));
    auto b = a;
    auto c = b;

    EXPECT_EQ(a.value(), b.value());
    EXPECT_EQ(b.value(), c.value());

    EXPECT_NE(a.value().c_str(), b.value().c_str());
    EXPECT_NE(b.value().c_str(), c.value().c_str());
    EXPECT_NE(a.value().c_str(), c.value().c_str());
}

TEST(StorageBox, move_operations_deleted_runtime_check) {
    // Cannot test at runtime but static_assert confirms no move
    static_assert(!std::is_move_constructible_v<StorageBox<TestStruct<int>>>);
    static_assert(!std::is_move_assignable_v<StorageBox<TestStruct<int>>>);
}

TEST(StorageBox, not_empty_after_put) {
    auto box = TestStruct<std::string>::store(std::string("hello"));
    EXPECT_TRUE(box.has_value());
}

TEST(StorageBox, put_and_get_complex_type) {
    auto box = TestStruct<std::string>::store(std::string("hello"));
    EXPECT_EQ(box.value(), "hello");
}

TEST(StorageBox, self_copy_assignment_explicit) {
    auto box = TestStruct<int>::store(123);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    box = box;
#pragma clang diagnostic pop
    EXPECT_TRUE(box.has_value());
    EXPECT_EQ(box.value(), 123);
}

TEST(StorageBox, self_copy_assignment_is_safe) {
    auto a = TestStruct<int>::store(42);
// we do this check already in operator=
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    a = a;
#pragma clang diagnostic pop
    EXPECT_TRUE(a.has_value());
    EXPECT_EQ(a.value(), 42);
}

TEST(StorageBox, works_with_various_types) {
    // int
    auto int_box = TestStruct<int>::store(7);
    EXPECT_EQ(int_box.value(), 7);

    // double
    auto double_box = TestStruct<double>::store(3.14);
    EXPECT_EQ(double_box.value(), 3.14);

    // user-defined struct
    struct Point {
        int x, y;
    };
    auto point_box = TestStruct<Point>::store(Point{1, 2});
    EXPECT_EQ(point_box.value().x, 1);
    EXPECT_EQ(point_box.value().y, 2);
}
