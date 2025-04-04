# Test Plan for Option

## Test Plan

### Callables
- Tests with `std::function`, lambdas, and function pointers wrapped inside `Some`.
  - Ensures that `Option` works correctly with callable types.

### Void and Nullptr
- Tests with `void*` and `const void*` wrapped inside `Some`.
  - Verifies that the `Option` works correctly when wrapped with null pointers of `void*` types.

### Pointer
- Tests with pointers to both `const` and non-`const` types wrapped inside `Some`.
  - Ensures `Option` works with pointer types as expected.

### Const Integral
- Tests with `const` integral types wrapped inside `Some`.
  - Verifies that the `Option` handles `const` integral types correctly.

### Plain Integral
- Tests with non-`const` integral types wrapped inside `Some`.
  - Ensures that `Option` works with plain integral types as expected.

### References
- **What needs to be done**: Create a test case for `Option` wrapping references, both non-const and const references (e.g., `int&` and `const int&`). This would ensure that `Option` works as expected for reference types.

### Move Semantics
- **What needs to be done**: Implement tests for move semantics for `Option`. Verify that the move constructor and move assignment operator behave correctly when using types like `std::unique_ptr` or non-copyable types.

### Shared Ownership (like `std::shared_ptr`)
- **What needs to be done**: Add a test for using `std::shared_ptr` with `Option`. Ensure that `Option` can handle types that have shared ownership semantics.

### Nested Option
- **What needs to be done**: Implement a test case for nesting `Option` types (e.g., `Option<Option<T>>`). Ensure that wrapping and unwrapping works as expected.

### Custom Types
- **What needs to be done**: Add tests for custom user-defined types (like structs or classes). Ensure that `Option` works well with user-defined types, especially those with custom copy/move constructors.

### Const/Non-const Mismatch
- **What needs to be done**: Implement tests for cases where `Option` is used with a non-const value but is expected to be treated as `const`. Ensure there are no unexpected mutations.

### Error Handling (if applicable)
- **What needs to be done**: If your `Option` type supports error handling (such as `Option::map` or `Option::flat_map`), you should test edge cases where the wrapped value is invalid or triggers an exception.
