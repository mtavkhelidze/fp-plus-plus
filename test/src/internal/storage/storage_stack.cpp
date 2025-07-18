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
};

TEST(StorageStack, copy_assignment_copies_value) {
    auto original = TestStruct<int>::store(123);
    auto copy = TestStruct<int>::store(0);
    copy = original;
    EXPECT_EQ(copy.value(), 123);
    EXPECT_EQ(original.value(), 123);
}

TEST(StorageStack, copy_constructor_copies_value) {
    auto original = TestStruct<int>::store(99);
    auto copy = original;
    EXPECT_EQ(copy.value(), 99);
    EXPECT_EQ(original.value(), 99);
}

TEST(StorageStack, self_assignment_does_nothing) {
    auto box = TestStruct<int>::store(123);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    box = box;  // self-assign
#pragma clang diagnostic pop

    EXPECT_EQ(box.value(), 123);
}

TEST(StorageStack, stores_and_returns_value) {
    auto box = TestStruct<int>::store(42);
    EXPECT_EQ(box.value(), 42);
}
