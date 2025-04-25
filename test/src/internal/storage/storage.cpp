#include <fp/internal/box.h>
#include <fp/internal/storage/storage_provider.h>
#include <fp/prelude/pure.h>
#include <gtest/gtest.h>

using namespace fp::internal::box;
using namespace fp::prelude;

template <template <typename> typename Data, typename A>
using StorageProvider = fp::internal::storage::StorageProvider<Data, A>;

template <typename A>
struct DataClass : public StorageProvider<DataClass, A> {
    using StorageProvider<DataClass, A>::StorageProvider;

    template <typename T>
    static auto apply(T&& value) {
        return DataClass{DataClass::store(value)};
    }
    auto value() const { return this->retrieve(); }
};

TEST(StorageProvider, backend_choice) {
    int arr[] = {1, 2, 3};
    DataClass da1 = pure<DataClass>(arr);
    EXPECT_TRUE(da1.is_box());
    EXPECT_FALSE(da1.is_stack());
    EXPECT_EQ(da1.value().at(2), 3);

    DataClass da2 = pure<DataClass>(42);
    EXPECT_FALSE(da2.is_box());
    EXPECT_TRUE(da2.is_stack());
    EXPECT_EQ(da2.value(), 42);
}

TEST(StorageProvider, empty_data) {
    int arr[] = {};
    DataClass da = pure<DataClass>(arr);
    EXPECT_TRUE(da.is_box());
    // EXPECT_EQ(da.value().size(), 0);
}
