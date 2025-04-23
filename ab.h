#ifndef AB_H
#define AB_H

namespace __private {
template <typename T>
struct __A {
    T value;
};
}  // namespace __private

template <typename T>
struct B {
  private:
    using A = __private::__A<T>;
    A a;
};
#endif  // AB_H
