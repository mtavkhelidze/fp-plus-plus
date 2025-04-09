#include <iostream>
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_BOX_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_BOX_H

#include "defs.h"

namespace fp {

template <typename T, typename... Ts>
struct Box {
  private:
    std::variant<std::unique_ptr<T>, std::unique_ptr<T*>> data;

  public:
    // --- Accessors
    [[nodiscard]] [[clang::annotate("nullable")]]
    auto getOrNull() const -> T* {
        if (data.index() == 0) {
            return std::get<std::unique_ptr<T>>(data).get();
        }
        if (data.index()) { return std::get<std::unique_ptr<T*>>(data).get(); }
        return nullptr;
    }

    // --- constructors
    // Concrete (includes things like A*)
    explicit Box(const T& t)
        requires(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>)
        : data{std::make_unique<T>(t)} {
        std::cerr << ">>> concrete: " << typeid(T).name() << "\n";
    }
    // Shared
    explicit Box(std::shared_ptr<T> ptr) : data(std::make_unique<T>(*ptr)) {
        std::cerr << ">>> shared: " << typeid(T).name() << "\n";
    }
    // Raw pointer
    explicit Box(T ptr)
        requires(std::is_pointer_v<T>)
        : data{std::make_unique<T>(ptr)} {
        std::cerr << ">>> raw pointer: " << typeid(T).name() << "\n";
    }
    // unique
    explicit Box(std::unique_ptr<T>& ptr) : data(std::move(ptr)) {
        std::cerr << ">>> unique: " << typeid(T).name() << "\n";
    }
    // Varargs
    explicit Box(const T&& t, Ts&&... ts)
        requires(sizeof...(Ts) > 0)
    {
        constexpr size_t size = sizeof...(Ts) + 1;
        auto xs = std::array<T, size>{std::move(t), std::move(ts)...};
        data = std::make_unique<T*>(std::move(xs.data()));
        std::cerr << ">>> varargs: " << typeid(T).name() << "\n";
    }
    // nullptr
    explicit Box(T /*np*/)
        requires std::is_null_pointer_v<T>
        : data{std::make_unique<T>(nullptr)} {
        std::cerr << ">>> nullptr: " << typeid(T).name() << "\n";
    }
    // Move-only
    explicit Box(T&& t)
        requires(
          std::is_move_constructible_v<T> && !std::is_copy_constructible_v<T>
        )
        : data{std::make_unique<T>(std::move(t))} {
        std::cerr << ">>> move-only: " << typeid(T).name() << "\n";
    }
    // --- Other constructors
    ~Box() = default;
    auto operator=(Box&&) -> Box& = default;
    auto operator=(const Box&) -> Box& = default;
    Box() = delete;
    Box(Box&&) = default;
    Box(const Box&) = default;
} FP_PLUS_PLUS_ALIGN_PACKED;

// Deduction guides
template <typename T>
Box(T&&) -> Box<std::decay_t<T>>;

template <typename U, std::size_t N>
Box(const std::array<U, N>&) -> Box<U*>;

Box(const char*) -> Box<std::string>;

}  // namespace fp

#endif  // FP_BOX_H
