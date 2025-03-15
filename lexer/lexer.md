# Compiler

In a compiler, there are two kinds of analysis going on simultaneously
1. Linear analysis - lexical analysis performed by the lexer
2. Hierarchial analysis - syntax analysis performed by the parser

In the overall compilation process, several steps occur:

Lexical analysis -> Syntax analysis -> Semantic analysis -> Intermediate code generation

During this process, the compiler manages a symbol table.


To build a compiler, we must program each of the parts ourselves: lexer, parser, semantic analyzer, intermediate code generator

# Designing a lexer
Before writing a lexer, we must be aware of the different types of keywords in a programming language.

1. KEYWORD - predefined words that have a predefined action
2. IDENTIFIER - user-defined word that represents a memory location
3. OPERATOR - logical operator, arithmetic operator, or bitwise operator
4. CONSTANT - a constant value or expression (string literal)
5. PUNCTUATION - for example, `;` and `,` are punctuations, as is `:`

A lexer turns the words in a programming language into a stream of tokens.
A token is one of the 5 things mentioned above.

```
Consider the statement:
int x = 5;

In this statement, there are 5 tokens:
int -> keyword
x -> identifier
= -> operator (assignment operator)
5 -> constant
; -> punctuation
```

A lexer analysis the given string and turns them into tokens. The given string is the source code btw.

So for oue first code, we will make a enum that will determine which token it is, given a single string literal.
For example, it will take the string literal "bool" and determine that it is a data type.

In C++, there are two kinds of enums: scoped and unscoped.
Unscoped enums are global so we will use those.

Now follow lexer.cpp
