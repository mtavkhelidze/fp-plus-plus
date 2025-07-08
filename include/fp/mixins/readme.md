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
