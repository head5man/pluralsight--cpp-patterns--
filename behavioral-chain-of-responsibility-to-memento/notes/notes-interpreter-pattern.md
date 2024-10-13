### Interpreter pattern

#### Gang of four quote
>Given a language, define a representation for its grammer along with an interpreter that uses the representation to interpret sentences in the language.

#### Calculator example
Expression `1+2`

`1`, `2` are terminal symbols
`+` is non terminal

In other words the `1` and `2` are child nodes of the `+` symbol and the `+` symbol has no child nodes.

To implement the interpreter pattern one has to implement lexing and parsing.

#### Interpreter structure

```mermaid
flowchart LR
ID-1 ~~~ ID-2 ~~~ ID-3
ID-4 ~~~ ID-5
ID-1(<b>AbstractExpression</b><br/>Declares an abstract interpret operation)

ID-2(<b>TerminalExpression</b><br/>Implements an interpret operation for terminal symbols)

ID-3(<b>NonTerminalExpression</b><br/>Implements an interpret operation for nonterminal symbols)

ID-4(<b>Context</b><br/>Contains the global information for the interpreter)

ID-5(<b>Client</b><br/>Builds an abstract syntax tree)
```

#### Why Interpreter?
- Express recurring problems as language
- Decrease complexity
- Increase efficiency
- Regular expressions
