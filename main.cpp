#include <iostream>

template <typename A>
struct Object {
  private:
    Object() = default;
    explicit Object(A value) : v(value) {}

  public:
    Object(const Object&) = delete;
    Object(Object&&) = delete;

    template <typename T>
    static Object<std::decay_t<T>> apply(T&& value) {
        return Object(std::forward<std::decay_t<T>>(value));
    }

  private:
    A v;
};

auto main() -> int {  //
    return 0;
}
