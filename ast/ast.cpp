// Follow ASTNotes.cpp for explanation of `virtual` keyword
// Follow ASTNotes.cpp for explanation of virtual destructors
// Follow 'misc.txt' for explanation of lvalue, rvalue, std::move(), std::unique_prt<>
#include <string>
#include <memory>

#include <vector>

/* ---------------- StmtAST ---------------- */
class StmtAST {
    public:
        virtual ~StmtAST() = default;
};

/* ---------------- ExprAST ---------------- */
class ExprAST : public StmtAST {
    public:
        // default destructor, virtualized
        virtual ~ExprAST() override = default;
};

class NumberExprAST : public ExprAST {
    double Val;
    public:
        // constructor
        NumberExprAST(double Val) : Val(Val) {};

        // destructor
        ~NumberExprAST() override = default;
};

class VariableExprAST : public ExprAST {
    std::string Name;

    public:
    // constructor
    VariableExprAST(const std::string& Name) : Name(Name) {};
    // const std::string& is an optimization. We will call it const&
    // with const&, we avoid copying the string more times than necessary
    // if an lvalue reference is provided as argument

    // with const&, we can read rvalue references too if the caller
    // chooses to provide that as an argument

    // with const&, we hand the decision of ownership transfer to the caller
    // and avoid stealing from the owner.

    // unforeseen stealing can lead to dangling references, and hence
    // memory leaks


    // Why not just use string& you ask?
    // Because std::string& only accepts lvalues references (compiler design)

    // destructor
    ~VariableExprAST() override = default;
};

class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LeftExpr;
    std::unique_ptr<ExprAST> RightExpr;

    // Why unique_ptr?
    // unique_ptr ensure two main things:
    // 1. Automatic memory management, 2. Efficient move semantics

    // Another thing unique_ptr ensure is that the ownership of the ExprAST is
    // owned by only one tree at a time. std::unique_ptr enforces this
    // behavior.

    public:
    // constructor
    BinaryExprAST(const char& Op, std::unique_ptr<ExprAST> LeftExpr, std::unique_ptr<ExprAST> RightExptr) : Op(Op), LeftExpr(std::move(LeftExpr)), RightExpr(std::move(RightExpr)) {}

    // destructor
    ~BinaryExprAST() override = default;
};

/* ---------------- AssignmentAST ---------------- */
class AssignmentAST : public StmtAST {
    // will have operator, lhs, rhs
    // lhs is always a variable reference
    // rhs may be an expression

    // since this body is the same across all assignments, I will bundle it
    std::string Variable;
    std::string AssignmentOperator; // = or += or /= etc.
    std::unique_ptr<ExprAST> Rhs;

    public:
    // constructor
    AssignmentAST(const std::string& Variable, const std::string& AssignmentOperator, std::unique_ptr<ExprAST> Rhs) : Variable(Variable), AssignmentOperator(AssignmentOperator), Rhs(std::move(Rhs)) {}

    // destructor
    ~AssignmentAST() override = default;
};

/* ---------------- ReturnAST ---------------- */
class ReturnAST {

    std::unique_ptr<ExprAST> ReturnExpr;

    public:
    // constructor
    ReturnAST(std::unique_ptr<ExprAST> ReturnExpr) : ReturnExpr(std::move(ReturnExpr)) {}

    // destructor
    ~ReturnAST() = default;
};

/* ---------------- FunctionAST ---------------- */
class FunctionAST {
    // we can bundle all properties because a function has the same
    // structure

    // in ExprAST, the expression could be variable-variable,
    // variable-number, or number-number. It implies that variable and
    // number are different entities altogether, and hence we made
    // separate classes for them

    std::string Name; // Name is a string of function identifier (function name)
    std::vector<std::string> Args; // Args is list of identifiers
    std::vector<std::unique_ptr<StmtAST>> Body; // Body is list of statements
    std::unique_ptr<ReturnAST> Return; // Return is return statement of function

    public:
    // constructor
    FunctionAST(const std::string& Name, std::vector<std::string> Args, std::vector<std::unique_ptr<StmtAST>> Body, std::unique_ptr<ReturnAST> ReturnExpr) : Name(Name), Args(std::move(Args)), Body(std::move(Body)), Return(std::move(ReturnExpr)) {}
    // remember, std::move transfers ownership from previous lvalue by
    // casting lvalue to rvalue reference type and changing ownership

    // destructor
    virtual ~FunctionAST() = default;
};

// Implementation ends here
// No control-flow statements are supported as of 15.03.2025
// TODO: Add control-flow statements