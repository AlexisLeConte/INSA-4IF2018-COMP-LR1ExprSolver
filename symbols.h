#ifndef SYMBOLS_H_INCLUDED
#define SYMBOLS_H_INCLUDED

// --------------------------------------------------------- C++ System Headers
#include <map>
#include <memory>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// Constants Definitions                                                     //
///////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------- Symbol Identifiers
namespace SID {

    // -------------------------------------------- Terminal Symbol Identifiers
    enum Terminal {
        END_OF_STREAM = 0,          // Stream termination symbol
        NUM = 1,                    // Floating-point number
        VAR = 2,                    // Floating-point variable
        OPEN_BRACKET = 3,           // Open bracket
        CLOSED_BRACKET = 4,         // Closed bracket
        OP_ADD = 5,                 // Arithmetic operator + (addition)
        OP_SUB = 6,                 // Arithmetic operator - (subtraction)
        OP_MUL = 7,                 // Arithmetic operator * (multiplication)
        OP_DIV = 8                  // Arithmetic operator / (division)
    };

    // ----------------------------------------- Nonterminal Symbol Identifiers
    enum Nonterminal {
        AXIOM = 100,                // Arithmetic expression (root)
        EXP = 101                   // Arithmetic expression (nested)
    };

}

///////////////////////////////////////////////////////////////////////////////
// class Symbol                                                              //
///////////////////////////////////////////////////////////////////////////////

class Symbol
{
public:
    // ----------------------------------------------- Constructor / Destructor
    Symbol(int identifier, bool terminal);
    Symbol(const Symbol & source) = delete;
    virtual ~Symbol() = default;

    // ------------------------------------------------ Public Member Functions
    virtual std::string text() const = 0;
    inline bool terminal() const { return m_terminal; }

    // --------------------------------------------------- Overloaded Operators
    Symbol & operator=(const Symbol & source) = delete;
    inline operator int() const { return m_identifier; }

protected:
    const int m_identifier;
    const bool m_terminal;
};

///////////////////////////////////////////////////////////////////////////////
// class EndOfStream : public Symbol                                         //
///////////////////////////////////////////////////////////////////////////////

class EndOfStream : public Symbol
{
public:
    // ----------------------------------------------- Constructor / Destructor
    EndOfStream();
    EndOfStream(const EndOfStream & source) = delete;
    virtual ~EndOfStream() = default;

    // ------------------------------------------------ Public Member Functions
    virtual std::string text() const;

    // --------------------------------------------------- Overloaded Operators
    EndOfStream & operator=(const EndOfStream & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class Operator : public Symbol                                            //
///////////////////////////////////////////////////////////////////////////////

class Operator : public Symbol
{
public:
    // ----------------------------------------------- Constructor / Destructor
    Operator(int identifier, const std::string & name);
    Operator(const Operator & source) = delete;
    virtual ~Operator() = default;

    // ------------------------------------------------ Public Member Functions
    virtual std::string text() const override;

    // --------------------------------------------------- Overloaded Operators
    Operator & operator=(const Operator & source) = delete;

protected:
    const std::string m_name;
};

///////////////////////////////////////////////////////////////////////////////
// class OpenBracket : public Operator                                       //
///////////////////////////////////////////////////////////////////////////////

class OpenBracket : public Operator
{
public:
    // ----------------------------------------------- Constructor / Destructor
    OpenBracket();
    OpenBracket(const OpenBracket & source) = delete;
    virtual ~OpenBracket() = default;

    // --------------------------------------------------- Overloaded Operators
    OpenBracket & operator=(const OpenBracket & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class ClosedBracket : public Operator                                     //
///////////////////////////////////////////////////////////////////////////////

class ClosedBracket : public Operator
{
public:
    // ----------------------------------------------- Constructor / Destructor
    ClosedBracket();
    ClosedBracket(const ClosedBracket & source) = delete;
    virtual ~ClosedBracket() = default;

    // --------------------------------------------------- Overloaded Operators
    ClosedBracket & operator=(const ClosedBracket & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class BinaryOperator : public Operator                                    //
///////////////////////////////////////////////////////////////////////////////

class BinaryOperator : public Operator
{
public:
    // ----------------------------------------------- Constructor / Destructor
    BinaryOperator(int indentifier, const std::string & name);
    BinaryOperator(const BinaryOperator & source) = delete;
    virtual ~BinaryOperator() = default;

    // ------------------------------------------------ Public Member Functions
    virtual double eval(double left_operand, double right_operand) const = 0;

    // --------------------------------------------------- Overloaded Operators
    BinaryOperator & operator=(const BinaryOperator & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class AddOperator : public BinaryOperator                                 //
///////////////////////////////////////////////////////////////////////////////

class AddOperator : public BinaryOperator
{
public:
    // ----------------------------------------------- Constructor / Destructor
    AddOperator();
    AddOperator(const AddOperator & source) = delete;
    virtual ~AddOperator() = default;

    // ------------------------------------------------ Public Member Functions
    virtual double eval(double left_operand, double right_operand) const override;

    // --------------------------------------------------- Overloaded Operators
    AddOperator & operator=(const AddOperator & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class SubOperator : public BinaryOperator                                 //
///////////////////////////////////////////////////////////////////////////////

class SubOperator : public BinaryOperator
{
public:
    // ----------------------------------------------- Constructor / Destructor
    SubOperator();
    SubOperator(const SubOperator & source) = delete;
    virtual ~SubOperator() = default;

    // ------------------------------------------------ Public Member Functions
    virtual double eval(double left_operand, double right_operand) const override;

    // --------------------------------------------------- Overloaded Operators
    SubOperator & operator=(const SubOperator & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class MulOperator : public BinaryOperator                                 //
///////////////////////////////////////////////////////////////////////////////

class MulOperator : public BinaryOperator
{
public:
    // ----------------------------------------------- Constructor / Destructor
    MulOperator();
    MulOperator(const MulOperator & source) = delete;
    virtual ~MulOperator() = default;

    // ------------------------------------------------ Public Member Functions
    virtual double eval(double left_operand, double right_operand) const override;

    // --------------------------------------------------- Overloaded Operators
    MulOperator & operator=(const MulOperator & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class DivOperator : public BinaryOperator                                 //
///////////////////////////////////////////////////////////////////////////////

class DivOperator : public BinaryOperator
{
public:
    // ----------------------------------------------- Constructor / Destructor
    DivOperator();
    DivOperator(const DivOperator & source) = delete;
    virtual ~DivOperator() = default;

    // ------------------------------------------------ Public Member Functions
    virtual double eval(double left_operand, double right_operand) const override;

    // --------------------------------------------------- Overloaded Operators
    DivOperator & operator=(const DivOperator & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class AtomicValue : public Symbol                                         //
///////////////////////////////////////////////////////////////////////////////

class AtomicValue : public Symbol
{
public:
    // ----------------------------------------------- Constructor / Destructor
    AtomicValue(int identifier);
    AtomicValue(const AtomicValue & source) = delete;
    virtual ~AtomicValue() = default;

    // ------------------------------------------------ Public Member Functions
    virtual double eval(const std::map<std::string, double> & values) const = 0;

    // --------------------------------------------------- Overloaded Operators
    AtomicValue & operator=(const AtomicValue & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class Number : public AtomicValue                                         //
///////////////////////////////////////////////////////////////////////////////

class Number : public AtomicValue
{
public:
    // ----------------------------------------------- Constructor / Destructor
    Number(double value);
    Number(const Number & source) = delete;
    virtual ~Number() = default;

    // ------------------------------------------------ Public Member Functions
    virtual std::string text() const override;
    virtual double eval(const std::map<std::string, double> & values) const override;

    // --------------------------------------------------- Overloaded Operators
    Number & operator=(const Number & source) = delete;

protected:
    const double m_value;
};

///////////////////////////////////////////////////////////////////////////////
// class Variable : public AtomicValue                                       //
///////////////////////////////////////////////////////////////////////////////

class Variable : public AtomicValue
{
public:
    // ----------------------------------------------- Constructor / Destructor
    Variable(const std::string & name);
    Variable(const Variable & source) = delete;
    virtual ~Variable() = default;

    // ------------------------------------------------ Public Member Functions
    virtual std::string text() const override;
    virtual double eval(const std::map<std::string, double> & values) const override;

    // --------------------------------------------------- Overloaded Operators
    Variable & operator=(const Variable & source) = delete;

protected:
    const std::string m_name;
};

///////////////////////////////////////////////////////////////////////////////
// class Expression : public Symbol                                          //
///////////////////////////////////////////////////////////////////////////////

class Expression : public Symbol
{
public:
    // ----------------------------------------------- Constructor / Destructor
    Expression();
    Expression(const Expression & source) = delete;
    virtual ~Expression() = default;

    // ------------------------------------------------ Public Member Functions
    virtual double eval(const std::map<std::string, double> & values) const = 0;

    // --------------------------------------------------- Overloaded Operators
    Expression & operator=(const Expression & source) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// class AtomicExpression : public Expression                                //
///////////////////////////////////////////////////////////////////////////////

class AtomicExpression : public Expression
{
public:
    // ----------------------------------------------- Constructor / Destructor
    AtomicExpression(std::unique_ptr<const AtomicValue> atomic_value);
    AtomicExpression(const Expression & source) = delete;
    virtual ~AtomicExpression() = default;

    // ------------------------------------------------ Public Member Functions
    virtual std::string text() const override;
    virtual double eval(const std::map<std::string, double> & values) const override;

    // --------------------------------------------------- Overloaded Operators
    AtomicExpression & operator=(const AtomicExpression & source) = delete;

protected:
    const std::unique_ptr<const AtomicValue> m_atomic_value;
};

///////////////////////////////////////////////////////////////////////////////
// class BinaryExpression : public Expression                                //
///////////////////////////////////////////////////////////////////////////////

class BinaryExpression : public Expression
{
public:
    // ----------------------------------------------- Constructor / Destructor
    BinaryExpression(
            std::unique_ptr<const Expression> left_operand,
            std::unique_ptr<const Expression> right_operand,
            std::unique_ptr<const BinaryOperator> binary_operator);
    BinaryExpression(const BinaryExpression & source) = delete;
    virtual ~BinaryExpression() = default;

    // ------------------------------------------------ Public Member Functions
    virtual std::string text() const override;
    virtual double eval(const std::map<std::string, double> & values) const override;

    // --------------------------------------------------- Overloaded Operators
    BinaryExpression & operator=(const BinaryExpression & source) = delete;

protected:
    const std::unique_ptr<const Expression> m_left_operand;
    const std::unique_ptr<const Expression> m_right_operand;
    const std::unique_ptr<const BinaryOperator> m_binary_operator;
};

///////////////////////////////////////////////////////////////////////////////
// class BracketedExpression : public Expression                             //
///////////////////////////////////////////////////////////////////////////////

class BracketedExpression : public Expression
{
public:
    // ----------------------------------------------- Constructor / Destructor
    BracketedExpression(
            std::unique_ptr<const Expression> inner_expression,
            std::unique_ptr<const OpenBracket> left_bracket,
            std::unique_ptr<const ClosedBracket> right_bracket);
    BracketedExpression(const BracketedExpression & source) = delete;
    virtual ~BracketedExpression() = default;

    // ------------------------------------------------ Public Member Functions
    virtual std::string text() const override;
    virtual double eval(const std::map<std::string, double> & values) const override;

    // --------------------------------------------------- Overloaded Operators
    BracketedExpression & operator=(const BracketedExpression & source) = delete;

protected:
    const std::unique_ptr<const Expression> m_inner_expression;
    const std::unique_ptr<const OpenBracket> m_left_bracket;
    const std::unique_ptr<const ClosedBracket> m_right_bracket;
};

///////////////////////////////////////////////////////////////////////////////
// class Axiom : public Symbol                                               //
///////////////////////////////////////////////////////////////////////////////

class Axiom : public Symbol
{
public:
    // ----------------------------------------------- Constructor / Destructor
    Axiom(std::unique_ptr<const Expression> expression);
    Axiom(const Axiom & source) = delete;
    virtual ~Axiom() = default;

    // ------------------------------------------------ Public Member Functions
    virtual std::string text() const override;
    virtual double eval(const std::map<std::string, double> & values) const;

    // --------------------------------------------------- Overloaded Operators
    Axiom & operator=(const Axiom & source) = delete;
    
protected:
    const std::unique_ptr<const Expression> m_expression;
};

#endif // SYMBOLS_H_INCLUDED
