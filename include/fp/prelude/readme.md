# Prelude

A functional toolbox. Imported by default with:

```
#include <fp/fp.h>

using namespace fp;
```

## Data Types

### Nothing

Represents absence of a value. Implements equality and ordering operators and
supports string conversion.

---

## Tools

### Cast Utilities

Type-safe casting helpers to convert raw types into suitable representations
within the library. Includes specializations for strings, arrays, tuples, void,
and pointers.

---

## Functions

### compose

Compose two functions: `compose(f, g)(x)` is `f(g(x))`. Equivalent to Haskell’s
`(.)` operator. Also known as function composition or
`andThen`.

---

### dollar

Dollar operator (`$`) for function application with low precedence. Useful for
reducing parentheses in nested function calls.

---

### flip

Flip the first two arguments of a binary function.  
`flip(f)(a, b)` is equivalent to `f(b, a)`.

---

### fmap

Generic mapping function for any Functor. Applies a function to the contents of
a functor, equivalent to `fa.map(f)`.

---

### identity

Identity function that returns its argument unchanged.  
Acts as the functional identity in function composition.

---

### pipe

Pipe operator (`|>`) that forwards a value into a function.  
Used to write clear and readable chained operations.

---

### pure

Injects a value into the context of a type constructor (such as a Functor or
Monad). Wraps a raw value into a computational context.
