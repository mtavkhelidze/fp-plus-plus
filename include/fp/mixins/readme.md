# Mixins

## WithValue

### Description

`WithValue` is a mixin that provides a general abstraction for storing values.
It automatically selects an appropriate storage backend (stack or heap) based on
the value type, and exposes standard methods such as `.value()`, `.has_value()`,
and `.equals()`. It also defines a static `apply(...)` method for
functional-style construction, enabling integration with `pure`.

Types using `WithValue` conform to the `HasValue` and `HasApply` concepts, and
`Eq` if the underlying type supports equality comparison. It is designed for use
as a composable mixin, and includes test-only methods to detect the chosen
backend at runtime.

### Mixins

* WithValue

#### Traits

* HasValue
* HasApply
* Eq

#### Prelude

* pure

## WithEq

### Description

`WithEq` is a mixin that provides value-based equality comparison by building on
top of `WithValue`.  
It uses the CRTP pattern to define an `equals` method that compares the
underlying values of the derived type instances.

This mixin exposes constructors by inheriting them from `WithValue` and can be
combined with other mixins to extend functionality.  
It does not define operators itself, focusing solely on the core equality logic.

### Mixins

* WithEq (inherits from `WithValue`)

#### Traits

* Eq (provides `.equals()` method)

### Prelude

* Supports use with `pure` through `WithValue`'s `apply` method.
