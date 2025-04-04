#include <memory>

namespace fp {
template <typename T>
struct Option;

template <typename T>
const auto Some(const T& value) {
    return Option<const T>(value);
}

template <typename T>
struct Option {
  public:
    std::shared_ptr<const T> ptr;

    // Overload for const T&
    explicit Option(const T& t) : ptr(std::make_shared<const T>(t)) {}

    // Constructor that takes a pointer to T and stores it
    explicit Option(T* t) : ptr(t) {}

    // Constructor that takes a shared pointer to const T and stores it
    explicit Option(std::shared_ptr<const T> t) : ptr(t) {}

    // Copy constructor
    Option(const Option& other) : ptr(other.ptr) {}

    // Delete move constructor to enforce copy-only semantics
    Option(Option&&) = delete;

    // Delete move assignment operator to force copy constructor usage
    Option& operator=(Option&&) = delete;
};

};  // namespace fp
