#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_BOX_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_BOX_H

#include <memory>

#include "defs.h"

namespace fp {

template <typename T, typename... Ts>
struct Box {
  private:
    std::variant<std::unique_ptr<T>, std::unique_ptr<T*>> data;

  public:
    // --- Accessors
    [[nodiscard]] [[clang::annotate("nullable")]]
    auto getOrNull() const -> std::shared_ptr<T> {
        if (data.index() == 0) {
            return std::shared_ptr<T>(std::get<std::unique_ptr<T>>(data)
            );  // Converts unique_ptr to shared_ptr
        }
        if (data.index() == 1) {
            return std::shared_ptr<T>(*std::get<std::unique_ptr<T*>>(data)
            );  // Convert the raw pointer inside unique_ptr<T*> to shared_ptr
        }
        return nullptr;  // No data in Box
    }
    // --- constructors
    // Concrete (includes things like A*)
    explicit Box(const T& t)
        requires(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>)
        : data{std::make_unique<T>(t)} {}
    // Shared
    explicit Box(std::shared_ptr<T> ptr) : data(std::make_unique<T>(*ptr)) {}
    // Raw pointer
    explicit Box(T ptr)
        requires(std::is_pointer_v<T>)
        : data{std::make_unique<T>(ptr)} {}
    // unique
    explicit Box(std::unique_ptr<T>& ptr) : data(std::move(ptr)) {}
    // Varargs
    explicit Box(const T&& t, Ts&&... ts)
        requires(sizeof...(Ts) > 0)
    {
        constexpr size_t size = sizeof...(Ts) + 1;
        auto xs = std::array<T, size>{std::move(t), std::move(ts)...};
        data = std::make_unique<T*>(std::move(xs.data()));
    }
    // nullptr
    explicit Box(T /* np */)
        requires std::is_null_pointer_v<T>
        : data{std::make_unique<T>(nullptr)} {}
    // Move-only
    explicit Box(T&& t)
        requires(
          std::is_move_constructible_v<T> && !std::is_copy_constructible_v<T>
        )
        : data{std::make_unique<T>(std::move(t))} {}
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
