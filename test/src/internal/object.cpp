#include <fp/internal/box.h>
#include <fp/internal/object.h>
#include <fp/prelude/pure.h>
#include <gtest/gtest.h>

using namespace fp::internal::box;

using namespace fp::prelude;

template <template <typename> typename Data, typename A>
using Object = fp::internal::object::Object<Data, A>;

template <typename A>
struct DataClass : public Object<DataClass, A> {
    using Object<DataClass, A>::Object;
};

TEST(Object, backend_choice) {
    int arr[] = {1, 2, 3};
    /// DataClass da1 = pure<DataClass>(arr);
    auto da1 = DataClass<std::vector<int>>::apply(arr);
    EXPECT_TRUE(da1.is_box());
    EXPECT_FALSE(da1.is_stack());
    EXPECT_EQ(da1.value().at(2), 3);

    DataClass da2 = pure<DataClass>(42);
    EXPECT_FALSE(da2.is_box());
    EXPECT_TRUE(da2.is_stack());
    EXPECT_EQ(da2.value(), 42);
}

TEST(Object, empty_data) {
    DataClass da = pure<DataClass>(nothing);
    EXPECT_TRUE(da.is_box());
    EXPECT_EQ(da.value(), nothing);
}
