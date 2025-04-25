#include <fp/internal/box.h>
#include <fp/internal/storage/storage_provider.h>
#include <gtest/gtest.h>

template <template <typename> typename TC, typename A>
using StorageBox = fp::internal::storage::StorageBox<TC, A>;

template <typename A>
using Box = fp::internal::box::Box<A>;

template <template <typename> class DataClass>
struct pure {
    template <typename T>
    static auto build(T&& value) {
        using BoxedT = Box<std::decay_t<T>>;
        using A = typename BoxedT::kind;
        return DataClass<A>::apply(std::forward<T>(value));
    }
};
template <typename A>
struct DataStruct : public StorageBox<DataStruct, A> {
    using StorageBox = StorageBox<DataStruct, A>;
    using StorageBox::StorageBox;

    template <typename T>
    static auto apply(T&& value) {
        return StorageBox::put(std::forward<T>(value));
    }
};

TEST(StorageBox, store) {  //
    int arr[3] = {1, 2, 3};
    auto sb = pure<DataStruct>::build(arr);
}
