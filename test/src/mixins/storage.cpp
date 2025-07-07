#include <fp/data/nothing.h>
#include <fp/internal/box.h>
#include <fp/mixins/storage.h>
#include <fp/operators/all.h>
#include <fp/prelude/pure.h>
#include <fp/traits/eq.h>
#include <gtest/gtest.h>

using namespace fp::data::nothing;

using namespace fp::operators::eq;
using namespace fp::prelude;

template <template <typename> typename Data, typename A>
using WithValue = fp::mixins::storage::WithValue<Data, A>;

template <typename A>
struct DataClass : WithValue<DataClass, A> {
    using WithValue<DataClass, A>::WithValue;
};

TEST(Mixin_WithApply, backend_choice) {
    constexpr int arr[] = {1, 2, 3};
    const DataClass da1 = pure<DataClass>(arr);
    // const auto da1 = DataClass<std::vector<int>>::apply(arr);
    EXPECT_TRUE(da1.is_box());
    EXPECT_FALSE(da1.is_stack());
    EXPECT_EQ(da1.value().at(2), 3);

    DataClass const da2 = pure<DataClass>(42);
    EXPECT_FALSE(da2.is_box());
    EXPECT_TRUE(da2.is_stack());
    EXPECT_EQ(da2.value(), 42);
}

TEST(Mixin_WithApply, empty_data) {
    DataClass const da = pure<DataClass>(nothing);
    EXPECT_TRUE(da.is_box());
    EXPECT_EQ(da.value(), nothing);
}

TEST(Mixin_WithApply, is_Eq_fundamental) {
    static_assert(fp::traits::eq::Eq<DataClass<int>>);
    DataClass const da1 = pure<DataClass>(42);
    DataClass const da2 = pure<DataClass>(42);
    DataClass const da3 = pure<DataClass>(24);
    EXPECT_TRUE(da1 == da2);
    EXPECT_TRUE(da1 != da3);
}

TEST(Mixin_WithApply, is_Eq_complex) {
    static_assert(fp::traits::eq::Eq<DataClass<std::vector<int>>>);
    DataClass const da1 = pure<DataClass>(std::vector{1, 2, 3});
    DataClass const da2 = pure<DataClass>(std::vector{1, 2, 3});
    DataClass const da3 = pure<DataClass>(std::vector{3, 2, 1});
    EXPECT_TRUE(da1 == da2);
    EXPECT_TRUE(da1 != da3);
}
