### Specs

Object:

* Must be an unary type-class instance
* Hold its value in Box
* Cannot be created other than through Object::apply, which is called by pure
* Cannot be copied or moved, only recreated via Object::aply
* Object::apply must decay given type and return Object with type decayed.

### COncept

| Spec Item                            | Enforced? |
|--------------------------------------|-----------|
| Unary typeclass instance             | Yes       |
| Box-backed storage                   | Design    |
| No direct construction               | Yes       |
| No copy or move                      | Yes       |
| Only constructible via decayingapply | Yes       |

### Instance

| Spec Requirement                                   | Conforms? |
|----------------------------------------------------|-----------|
| Unary typeclass instance                           | Yes       |
| Holds value in `Box`                               | Yes       |
| Cannot be created other than through `apply`       | Yes       |
| Cannot be copied or moved                          | Yes       |
| `apply` decays input and returns `Object<decayed>` | Yes       |
