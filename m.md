| semiarrow | pipe |
|:––|:—|
| Suggests monadic bind (>>=) from Haskell / functional programming. | Suggests piping (|>) from F#, Elixir, and shell-style chaining. |
| Semantically means: “do something more, stepwise.” (usually monadic context) | Semantically means: “pass value through transformations.” |
| Great if you treat a >= f as bind (“apply function to a value”). | Perfect if you treat a | f as pipe (“flow the value through function”). |
| Might confuse newcomers unfamiliar with FP if no monadic meaning behind it. | Very intuitive, even outside FP — “pipes” are everywhere. |
| Suggests more “binding” / “stepwise application.” | Suggests “flow” / “transformation chain.” |
