#include <fp/core/core.h>
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
        return Base::put(std::forward<decltype(x)>(x));
    }

    auto value() const -> auto& { return this->get(); }
};

TEST(StorageBox, copy_assignment_is_shallow) {
    auto a = TestStruct<std::string>::store(std::string("foo"));
    // Get the address of the string data in 'a'
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto a_ptr = (unsigned long)(a.value().c_str());
#pragma clang diagnostic pop

    TestStruct<std::string> b =
      TestStruct<std::string>::store(std::string("bar"));

    b = a;  // copy assignment

    EXPECT_EQ(b.value(), a.value());  // Content is equal ("foo")
    EXPECT_EQ((unsigned long)(b.value().c_str()), a_ptr);
}

TEST(StorageBox, copy_constructor_preserves_value) {
    auto a = TestStruct<std::string>::store("abc");
    auto b = a;
    EXPECT_EQ(b.value(), "abc");
}

TEST(StorageBox, const_accessors) {
    auto box = TestStruct<std::string>::store(std::string("const test"));
    const auto& const_box = box;
    EXPECT_EQ(const_box.value(), "const test");
}

TEST(StorageBox, doesnt_allow_move) {
    static_assert(
      !std::is_move_constructible_v<StorageBox<TestStruct<std::string>>>,
      "StorageBox should not be move constructible"
    );
    static_assert(
      !std::is_move_assignable_v<StorageBox<TestStruct<std::string>>>,
      "StorageBox should not be move assignable"
    );
}

TEST(StorageBox, multiple_copies_share_data) {  // Renamed for clarity
    auto a = TestStruct<std::string>::store(std::string("copytest"));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto a_ptr = (unsigned long)(a.value().c_str());
#pragma clang diagnostic pop

    auto b = a;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto b_ptr = (unsigned long)(b.value().c_str());  // Should be same as a_ptr
#pragma clang diagnostic pop

    auto c = b;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto c_ptr = (unsigned long)(c.value().c_str());  // Should be same as a_ptr
#pragma clang diagnostic pop

    EXPECT_EQ(a.value(), b.value());
    EXPECT_EQ(b.value(), c.value());

    EXPECT_EQ(a_ptr, b_ptr);
    EXPECT_EQ(b_ptr, c_ptr);
    EXPECT_EQ(a_ptr, c_ptr);
}

TEST(StorageBox, put_and_get_complex_type) {
    auto box = TestStruct<std::string>::store(std::string("hello"));
    EXPECT_EQ(box.value(), "hello");
}

TEST(StorageBox, self_copy_assignment_is_safe) {
    auto a = TestStruct<std::string>::store(std::string("safe"));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    a = a;
#pragma clang diagnostic pop
    EXPECT_EQ(a.value(), "safe");
}

TEST(StorageBox, stores_nothing_type_safely) {
    auto box = TestStruct<Nothing>::store(nothing);
}

TEST(StorageBox, works_with_custom_struct) {
    struct MyStruct {
        int x;
        std::string y;
        bool operator==(const MyStruct&) const = default;
    };

    MyStruct input{42, "hello"};
    auto box = TestStruct<MyStruct>::store(input);
    EXPECT_EQ(box.value(), input);
}
