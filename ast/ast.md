# AST - Abstract Syntax Tree

Abstract Syntax Tree is a tree data structure stores the structure of source code.

Why tree? Well, a tree just happens to be one of the best ways to represent the structure of source code. This is because source code itself has a hierarchial structure, which the three can represnt perfectly.

ASTs are best used for the following cases:
1. Expressions - arithmetic, boolean, assignment, etc.
2. Control flow - conditions, loops, return statements, etc.
3. Functions - ??
4. Modules and Programs and other features

The AST we will build is going to include the following:
1. Expression AST - arithmetic, binary, reference of variable
2. Function AST

Why an AST for reference of variable?
Because in an expression, there can be variables that do not have a fixed value. It may have a value that is only determined at runtime.

For example, consider math.random() produces a floating point precise to 5 decimal places
int x = math.random() * 1e5;
cout << x + 10;

In the example, the compiler does not inherently know the value of x until runtime.

So how do we go about making an AST?
Here is the process:

1. Determine different components of AST and make corresponding classes for each of them.
2. Build the parser which is the one that actually creates the tree (with nodes and stuff).

## Components of AST

Main components and sub components are listed below.
```
1. Expression AST (arithmetic)
    1.1 For operation on constants -> represent constants in the tree, like '5.2'
    1.2 For binary operation (like x + 4; y + z) -> to evaluate: operand1 operation operand2 (root node)
    1.3 For referencing a variable -> represnt variables in the tree, like 'x' in 'x + 4'
```

From the above explanation, we should be able to determine what each node holds in an expression AST:
One node can hold a constant, one can hold a variable, one can perform binary operation on two entities.

In an arithmetic component, three types of nodes that exist are described above.

In a assignment expression (int x = 4), three types of nodes exist again. Variable name, assignment operator, and value.
```
2. Expression AST (assignment)
    2.1 For operation on constant -> to hold the constant literal
    2.2 For referencing a variable -> to hold the name of the variable
    2.3 For assignment operator -> to hold the assignment operator (=, -=, +=, /=, *=, etc.)
```

However, this structure of an assignment expression AST is flawed. For you see, there can an arithmetic expression on the right side!

int x = y + 2;

Thus the correct structure would be as follows:
```
2. Expression AST (assignment)
    2.1 For assignment variable -> to hold the name of the variable on LHS
    2.2 For expression evaluation -> arithmetic evaluation on RHS (arithmetic expression AST)
    2.3 For assignment operator -> like '=', '+=', '/=', etc. (root node)

The expression evaluation is of course arithmetic, and will have its own tree:
2. Expression AST (assignment)
    2.1 For assignment variable -> to hold the name of the variable on LHS
    2.2 For expression evaluation -> arithmetic evaluation on RHS (arithmetic expression AST)
        2.2.1 For operation on constant -> to hold the constant literal
        2.2.2 For referencing a variable -> to hold the name of the variable
        2.2.3 For binary operation -> aka, the operation to perform (add, subtract, etc.)
    2.3 For assignment operator -> like '=', '+=', '/=', etc. (root node)

3. Function AST
    3.1 Return type -> a node of its own which contains the return type of the function
    3.2 Function identifier -> to identify the function by its name (root node)
    3.3 Function parameters -> to determine which arguments the function takes (sub-tree)
    3.4 Function body -> contains multiple sub-trees for each line of instruction
```

Why is the function parameter itself a tree (aka sub-tree of Function AST)?
Consider a function that takes 2 arguments. This is how its structure will look like:
```
3. Function AST
    3.1 Return type -> a node of its own which contains the return type of the function
    3.2 Function identifier -> to identify the function by its name (root node)
    3.3 Function parameters -> to determine which arguments the function takes (sub-tree)
        3.3.1 paramter1 (root node, child node 1)
            3.3.1.1 parameter1 type
            3.3.1.2 parameter1 name (identifier)
        3.3.2 parameter2 (root node, child node 2)
            3.3.2.1 parameter2 type
            3.3.2.2 parameter2 name (identifier)
    3.4 Function body -> contains multiple sub-trees for each line of instruction
```

For a function with no parameters, the function parameter sub-tree will contain no child nodes.

As for the function body, consider this little function:

```
int foo(int y) {
    int x = y + 4;
    return x;
}
```
The tree for this would be:

```
1. foo (root node, tree starts here)
    1.1 return type: int
    1.2 parameters:
        1.2.1 parameter 1
            1.2.1.1 type: int
            1.2.1.2 identifier: y
    1.3 body:
        1.3.1 assignment tree:
            1.3.1.1 assignment operator: =
            1.3.1.2 LHS (identifier): x
            1.3.1.3 RHS (expression):
                1.3.1.3.1 binary operation (root of this sub-tree, sub-tree itself is a child)
                1.3.1.3.2 variable reference: y
                1.3.1.3.3 constant literal: 4
        1.3.2 statment tree: IDK WHAT THIS IS return x; let's just say :)
```

## Design of ASTs

For each kind of AST, create a class. This class will be the base class for a tree, and it may as well act as its independent node in the grander scheme of things. For example, expression AST and assignment AST both being child nodes of some other AST.

For each of these AST classes, create child classes that inherit the base class. We do not make individual classes for each and every kind of entity and rather create child classes for different kinds of ASTs. This is because any kind of AST is self-contained, and it represents a generic entity, independent of any other entity.

It represents a higher level of abstraction, not individual tokens.

For example, the expression AST is a separate, independent, self-contained entity (tree) than assignment AST or function AST.

## Structure of expression AST

```
// base class for expression AST
class ExprAST {}

// child classes:

// 1. for constant
class ConstantLiteral : public ExprAST {} // this class will hold a constant literal

// 2. for variable
class VariableReference : public ExprAST {} // this will hold the reference to a variable

// 3. for binary operator
class BinaryOpAST : public ExprAST {} // this CAN contain other expression ASTs, for example 1 + 2 + y
```


More precisely, the binary operation AST can contain two other expression ASTs. This is because an operand can itself be an expression, forming a tree like structure.

For example, 1 + 2 + y, the tree looks like this:
```
    (+)
   /   \
  1    (+)
      /   \
     2     y
```

Now let us look at what is inside the base class and each child classes. Follow ast.cpp from here.