#include <fp/fp.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <bitset>
#include <chrono>
#include <deque>
#include <filesystem>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

using ::testing::_;
using ::testing::Test;

using namespace fp;

// NOLINTBEGIN: literal

TEST(Box_Construction_Exotic, can_hold_nullptr) {
    auto box = Box(nullptr);
    static_assert(std::is_same_v<Box<nullptr_t>, decltype(box)>);
}

TEST(Box_Construction_Exotic, literal_array) {
    auto box = Box{1, 2, 3};
    static_assert(std::is_same_v<Box<int, int, int>, decltype(box)>);
}

TEST(Box_Construction_Exotic, literal_string) {
    auto box = Box("hello");
    static_assert(std::is_same_v<Box<std::string>, decltype(box)>);
}

TEST(Box_Construction_Exotic, can_hold_void_pointer) {
    void* ptr = nullptr;
    auto box = Box(ptr);
    static_assert(std::is_same_v<Box<void*>, decltype(box)>);
}

TEST(Box_Construction_Exotic, can_hold_magic_boxes) {
    // as expected, this works
    auto box = Box<Box<int>>(Box(10));
    static_assert(std::is_same_v<Box<Box<int>>, decltype(box)>);
    // but this works too :)
    auto magic_box = Box(Box(Box(10)));
    static_assert(std::is_same_v<Box<int>, decltype(magic_box)>);
}

TEST(Box_Construction_Literal, can_hold_int) {
    auto box = Box(10);
    auto s = 13;
    static_assert(std::is_same_v<Box<int>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_double) {
    auto box = Box(10.5);
    static_assert(std::is_same_v<Box<double>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_char) {
    auto box = Box('a');
    static_assert(std::is_same_v<Box<char>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_bool) {
    auto box = Box(true);
    static_assert(std::is_same_v<Box<bool>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_float) {
    auto box = Box(10.5f);
    static_assert(std::is_same_v<Box<float>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_string) {
    auto box = Box(std::string("hello"));
    static_assert(std::is_same_v<Box<std::string>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_vector) {
    auto box = Box(std::vector<int>{1, 2, 3});
    static_assert(std::is_same_v<Box<std::vector<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_pair) {
    auto box = Box(std::pair<int, double>{1, 2.5});
    static_assert(std::is_same_v<Box<std::pair<int, double>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_shared_ptr) {
    auto box = Box(std::make_shared<int>(10));
    static_assert(std::is_same_v<Box<std::shared_ptr<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_unique_ptr) {
    auto box = Box(std::make_unique<int>(10));
    static_assert(std::is_same_v<Box<std::unique_ptr<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_optional) {
    auto box = Box(std::optional<int>{10});
    static_assert(std::is_same_v<Box<std::optional<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_tuple) {
    auto box = Box(std::tuple<int, float, std::string>{1, 2.5f, "hello"});
    static_assert(
      std::is_same_v<Box<std::tuple<int, float, std::string>>, decltype(box)>
    );
}

TEST(Box_Construction_Literal, can_hold_map) {
    auto box = Box(std::map<int, double>{{1, 2.5}, {2, 3.5}});
    static_assert(std::is_same_v<Box<std::map<int, double>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_unordered_map) {
    auto box = Box(std::unordered_map<int, double>{{1, 2.5}, {2, 3.5}});
    static_assert(
      std::is_same_v<Box<std::unordered_map<int, double>>, decltype(box)>
    );
}

TEST(Box_Construction_Literal, can_hold_set) {
    auto box = Box(std::set<int>{1, 2, 3});
    static_assert(std::is_same_v<Box<std::set<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_unordered_set) {
    auto box = Box(std::unordered_set<int>{1, 2, 3});
    static_assert(std::is_same_v<Box<std::unordered_set<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_array) {
    auto box = Box(std::array<int, 3>{1, 2, 3});
    static_assert(std::is_same_v<Box<std::array<int, 3>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_function) {
    auto box = Box(std::function<int(int)>{[](int x) { return x * 2; }});
    static_assert(std::is_same_v<Box<std::function<int(int)>>, decltype(box)>);
}

TEST(Box_Construction_Literal, can_hold_variant) {
    auto box = Box(std::variant<int, double>{10});
    static_assert(std::is_same_v<Box<std::variant<int, double>>, decltype(box)>
    );
}

TEST(Box_Construction_Literal_Extra, can_hold_unsigned_int) {
    auto box = Box<unsigned int>(10);
    static_assert(std::is_same_v<Box<unsigned int>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_long) {
    auto box = Box<long>(10000000000);
    static_assert(std::is_same_v<Box<long>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_unsigned_long) {
    auto box = Box<unsigned long>(10000000000);
    static_assert(std::is_same_v<Box<unsigned long>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_short) {
    auto box = Box<short>(10);
    static_assert(std::is_same_v<Box<short>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_unsigned_short) {
    auto box = Box<unsigned short>(10);
    static_assert(std::is_same_v<Box<unsigned short>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_unsigned_char) {
    auto box = Box<unsigned char>('a');
    static_assert(std::is_same_v<Box<unsigned char>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_long_long) {
    auto box = Box<long long>(1000000000000);
    static_assert(std::is_same_v<Box<long long>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_unsigned_long_long) {
    auto box = Box<unsigned long long>(1000000000000);
    static_assert(std::is_same_v<Box<unsigned long long>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_wchar_t) {
    auto box = Box<wchar_t>(L'a');
    static_assert(std::is_same_v<Box<wchar_t>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_signed_char) {
    auto box = Box(static_cast<signed char>('a'));
    static_assert(std::is_same_v<Box<signed char>, decltype(box)>);
}
TEST(Box_Construction_Literal_Extra, can_hold_int8_t) {
    auto box = Box(static_cast<int8_t>(10));
    static_assert(std::is_same_v<Box<int8_t>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_int16_t) {
    auto box = Box(static_cast<int16_t>(10));
    static_assert(std::is_same_v<Box<int16_t>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_int32_t) {
    auto box = Box(static_cast<int32_t>(10));
    static_assert(std::is_same_v<Box<int32_t>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_int64_t) {
    auto box = Box(static_cast<int64_t>(10));
    static_assert(std::is_same_v<Box<int64_t>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_uint8_t) {
    auto box = Box(static_cast<uint8_t>(10));
    static_assert(std::is_same_v<Box<uint8_t>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_uint16_t) {
    auto box = Box(static_cast<uint16_t>(10));
    static_assert(std::is_same_v<Box<uint16_t>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_uint32_t) {
    auto box = Box(static_cast<uint32_t>(10));
    static_assert(std::is_same_v<Box<uint32_t>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_uint64_t) {
    auto box = Box(static_cast<uint64_t>(10));
    static_assert(std::is_same_v<Box<uint64_t>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_bitset) {
    auto box = Box(std::bitset<8>(0b10101010));
    static_assert(std::is_same_v<Box<std::bitset<8>>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_deque) {
    auto box = Box(std::deque<int>{1, 2, 3});
    static_assert(std::is_same_v<Box<std::deque<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_list) {
    auto box = Box(std::list<int>{1, 2, 3});
    static_assert(std::is_same_v<Box<std::list<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_queue) {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    auto box = Box(q);
    static_assert(std::is_same_v<Box<std::queue<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_stack) {
    std::stack<int> s;
    s.push(1);
    s.push(2);
    auto box = Box(s);
    static_assert(std::is_same_v<Box<std::stack<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_priority_queue) {
    std::priority_queue<int> pq;
    pq.push(2);
    pq.push(1);
    auto box = Box(pq);
    static_assert(std::is_same_v<Box<std::priority_queue<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_array_template) {
    auto box = Box(std::array<int, 2>{1, 2});
    static_assert(std::is_same_v<Box<std::array<int, 2>>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_shared_ptr_again) {
    auto box = Box(std::shared_ptr<int>(new int(5)));
    static_assert(std::is_same_v<Box<std::shared_ptr<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_weak_ptr) {
    auto sp = std::make_shared<int>(5);
    auto box = Box(std::weak_ptr<int>(sp));
    static_assert(std::is_same_v<Box<std::weak_ptr<int>>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_reference_wrapper) {
    int x = 42;
    auto box = Box(std::ref(x));
    static_assert(
      std::is_same_v<Box<std::reference_wrapper<int>>, decltype(box)>
    );
}

TEST(Box_Construction_Literal_Extra, can_hold_regex) {
    auto box = Box(std::regex("a*b"));
    static_assert(std::is_same_v<Box<std::regex>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_duration) {
    auto box = Box(std::chrono::seconds(5));
    static_assert(std::is_same_v<Box<std::chrono::seconds>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_time_point) {
    auto box = Box(std::chrono::system_clock::now());
    static_assert(std::is_same_v<
                  Box<std::chrono::time_point<std::chrono::system_clock>>,
                  decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_filesystem_path) {
    auto box = Box(std::filesystem::path("/tmp/test"));
    static_assert(std::is_same_v<Box<std::filesystem::path>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_stringstream) {
    std::stringstream ss;
    auto box = Box(std::move(ss));
    static_assert(std::is_same_v<Box<std::stringstream>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_ostringstream) {
    std::ostringstream oss;
    auto box = Box(std::move(oss));
    static_assert(std::is_same_v<Box<std::ostringstream>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_istringstream) {
    std::istringstream iss("hello");
    auto box = Box(std::move(iss));
    static_assert(std::is_same_v<Box<std::istringstream>, decltype(box)>);
}

TEST(Box_Construction_Literal_Extra, can_hold_empty_tuple) {
    auto box = Box(std::tuple<>{});
    static_assert(std::is_same_v<Box<std::tuple<>>, decltype(box)>);
}

// NOLINTEND
