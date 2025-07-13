
#include <fp/core/nothing.h>
#include <fp/internal/storage/storage_stack.h>
#include <gtest/gtest.h>

using namespace fp::core;
using namespace fp::internal::storage;

template <typename A>
struct TestStruct : StorageStack<TestStruct<A>> {
    using Base = StorageStack<TestStruct<A>>;
    using Base::Base;

    static auto store(auto&& x) -> auto {
        return Base::put(std::forward<decltype(x)>(x));
    }

    auto value() const -> auto& { return this->get(); }
    auto has_value() const { return !this->empty(); }
};

TEST(StorageStack, stores_and_returns_value) {
    auto box = TestStruct<int>::store(42);
    ASSERT_TRUE(box.has_value());
    EXPECT_EQ(box.value(), 42);
}

TEST(StorageStack, default_constructs_empty_with_correct_type) {
    TestStruct<int&> box;
    EXPECT_FALSE(box.has_value());
    static_assert(
      std::same_as<decltype(std::declval<decltype(box)>().value()), const int&>
    );
}

TEST(StorageStack, self_assignment_does_nothing) {
    auto box = TestStruct<int>::store(123);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    box = box;  // self-assign
#pragma clang diagnostic pop

    EXPECT_EQ(box.value(), 123);
}
