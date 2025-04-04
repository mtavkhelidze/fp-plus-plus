# Test Plan for Option

# Option Design Overview

## Overview

`Option<T>` is a monadic type representing an optional value, which can either
contain a value of type `T` or be empty (`None`). Thread safety is not enforced
by default and should be handled externally if needed.

This implementation allows handling references and pointers efficiently, without
unnecessary copying. It is designed to be flexible enough to accommodate values,
references, and pointers, while maintaining strong type safety and performance
characteristics.

## Goals

1. **Preserve reference constantness**: When storing references, we want to
   ensure that the references themselves remain constant.
2. **Support flexible value, reference, and pointer handling**: `Option<T>`
   should allow storing values, references, and pointers efficiently.
3. **Explicit distinction between `None<T>` and `Some(nullptr)`**: We aim to
   treat `nullptr` as a valid value, but distinct from the `None` state.
4. **Avoid unnecessary allocations and copies**: Where possible, we want to
   minimize unnecessary memory allocations and object copying.
5. **Provide intuitive and consistent behavior**: Across different types,
   `Option<T>` should behave in a consistent and predictable manner, both for
   `T` values and for references/pointers.

## Design

The core of this design involves using `std::variant` to store the value in
different forms. This allows `Option<T>` to handle values, references, and
pointers in a flexible and efficient manner.

### Type Representation

`Option<T>` is represented as:

```cpp
std::variant<T, std::reference_wrapper, T*, std::nullptr_t>
```

Where:

- `T` stores a regular value of type `T`.
- `std::reference_wrapper<T>` stores a reference to an existing object, ensuring
  the reference is treated as an immutable value in the `Option` (making it
  immutable in this context).
- `T*` stores a pointer to `T` (which may be `nullptr`).
- `std::nullptr_t` is used exclusively for `Option<void>`, indicating a valid "
  empty" state that isn’t a `None` but rather a "null success" case.

### Construction Rules

Here’s how various expressions will work:

| Expression            | Resulting Type | In Variant     | Meaning                             |
|-----------------------|----------------|----------------|-------------------------------------|
| `Some(42)`            | `Option<int>`  | `T`            | Holds integer `42`                  |
| `Some(ptr)`           | `Option<T*>`   | `T*`           | Holds pointer `ptr`                 |
| `Some(nullptr)`       | `Option<void>` | `nullptr_t`    | Represents "exists but null"        |
| `Some<int*>(nullptr)` | `Option<int*>` | `T*` (nullptr) | Holds `nullptr` explicitly for `T*` |
| `None`                | `Option<void>` | -              | Represents absence of value         |
| `None<T>`             | `Option<T>`    | -              | Represents absence of `T`           |

### Special Considerations

1. **`Some(nullptr)`**: This is treated as `Option<void>`, not `Option<T*>`,
   because it signifies a "valid null" state. It indicates that there is a valid
   entity (the null pointer), but there is no actual value.

2. **`Some<int*>(nullptr)`**: This results in `Option<int*>` with `nullptr`
   stored as a valid pointer value. It's important to note that we explicitly
   treat `nullptr` as a valid value for pointers.

3. **Distinction Between `None<T>` and `Some<int*>(nullptr)`**: These are
   different. `None<T>` represents an absent value, while `Some<int*>(nullptr)`
   represents an explicit null pointer in an option holding pointers. This
   distinction ensures that `nullptr` is treated differently from an absent
   value.

4. **References Stored in `Option<T&>`**: References are preserved with their
   mutability. If you store a reference in an `Option<T&>`, it will retain the
   reference’s mutability, enabling modification of the underlying value if
   necessary, without copying the object.

### Expected Use Cases

- **`Some<T>`**: When you have a value of type `T` and you want to encapsulate
  it as an optional.
- **`Some<T*>`**: When working with pointers, and you may want to encapsulate a
  `nullptr` or a valid pointer.
- **`Some(nullptr)`**: Special case, used when the value is optional, but the
  lack of a value should be treated as a valid, meaningful state (for example,
  when null means "success" or "expected failure").
- **`None<T>`**: Represents a true "absence" of value, which can be handled
  gracefully in monadic operations like `map`, `flat_map`, etc.

## Behavior Considerations

1. **`Some(nullptr)` is treated as `Option<void>`**: This ensures that `None`
   and `Some(nullptr)` are distinct and do not mix the absence of value with the
   null pointer scenario.

2. **`Some<int*>(nullptr)` is valid for `Option<int*>`**: This results in an
   option that holds a pointer, and explicitly storing `nullptr` inside an
   option of type `T*` provides a meaningful representation of the absence of a
   value.

3. **`Some<T&>`**: When you store references, the `Option` behaves like a
   reference holder and guarantees that the reference stays constant, allowing
   modification of the underlying object without creating a copy.

4. **Avoiding unnecessary allocations**: By handling references and pointers
   directly (without copying unless necessary), we avoid extra allocations. This
   leads to better performance when working with large objects or complex data
   structures.

## Test Plan

### Callables

- Tests with `std::function`, lambdas, and function pointers wrapped inside
  `Some`.
    - Ensures that `Option` works correctly with callable types.

### Void and Nullptr

- Tests with `void*` and `const void*` wrapped inside `Some`.
    - Verifies that the `Option` works correctly when wrapped with null pointers
      of `void*` types.

### Pointer

- Tests with pointers to both `const` and non-`const` types wrapped inside
  `Some`.
    - Ensures `Option` works with pointer types as expected.

### Const Integral

- Tests with `const` integral types wrapped inside `Some`.
    - Verifies that the `Option` handles `const` integral types correctly.

### Plain Integral

- Tests with non-`const` integral types wrapped inside `Some`.
    - Ensures that `Option` works with plain integral types as expected.

### References

- **What needs to be done**: Create a test case for `Option` wrapping
  references, both non-const and const references (e.g., `int&` and
  `const int&`). This would ensure that `Option` works as expected for reference
  types.

### Move Semantics

- **What needs to be done**: Implement tests for move semantics for `Option`.
  Verify that the move constructor and move assignment operator behave correctly
  when using types like `std::unique_ptr` or non-copyable types.

### Shared Ownership (like `std::shared_ptr`)

- **What needs to be done**: Add a test for using `std::shared_ptr` with
  `Option`. Ensure that `Option` can handle types that have shared ownership
  semantics.

### Nested Option

- **What needs to be done**: Implement a test case for nesting `Option` types (
  e.g., `Option<Option<T>>`). Ensure that wrapping and unwrapping works as
  expected.

### Custom Types

- **What needs to be done**: Add tests for custom user-defined types (like
  structs or classes). Ensure that `Option` works well with user-defined types,
  especially those with custom copy/move constructors.

### Const/Non-const Mismatch

- **What needs to be done**: Implement tests for cases where `Option` is used
  with a non-const value but is expected to be treated as `const`. Ensure there
  are no unexpected mutations.

### Error Handling (if applicable)

- **What needs to be done**: If your `Option` type supports error handling (such
  as `Option::map` or `Option::flat_map`), you should test edge cases where the
  wrapped value is invalid or triggers an exception.
