// --------------------------------------------------------- C++ System Headers
#include <map>
#include <memory>
#include <sstream>
#include <string>

// ------------------------------------------------------------ Project Headers
#include "symbols.h"

// --------------------------------------------------------------------- Macros
#define UNUSED_PARAMETER(X) (void)(X) // Ignore "unused parameter" warnings

///////////////////////////////////////////////////////////////////////////////
// class Symbol                                                              //
///////////////////////////////////////////////////////////////////////////////

Symbol::Symbol(int identifier, bool terminal) :
    m_identifier(identifier),
    m_terminal(terminal)
{}

///////////////////////////////////////////////////////////////////////////////
// class EndOfStream : public Symbol                                         //
///////////////////////////////////////////////////////////////////////////////

EndOfStream::EndOfStream() :
    Symbol(SID::END_OF_STREAM, true)
{}

std::string EndOfStream::text() const
{
    return "$";
}

///////////////////////////////////////////////////////////////////////////////
// class Operator : public Symbol                                            //
///////////////////////////////////////////////////////////////////////////////

Operator::Operator(int identifier, const std::string & name) :
    Symbol(identifier, true), m_name(name)
{}

std::string Operator::text() const
{
    return m_name;
}

///////////////////////////////////////////////////////////////////////////////
// class OpenBracket : public Operator                                       //
///////////////////////////////////////////////////////////////////////////////

OpenBracket::OpenBracket() :
    Operator(SID::OPEN_BRACKET, "(")
{}

///////////////////////////////////////////////////////////////////////////////
// class ClosedBracket : public Operator                                     //
///////////////////////////////////////////////////////////////////////////////

ClosedBracket::ClosedBracket() :
    Operator(SID::CLOSED_BRACKET, ")")
{}

///////////////////////////////////////////////////////////////////////////////
// class BinaryOperator : public Operator                                    //
///////////////////////////////////////////////////////////////////////////////

BinaryOperator::BinaryOperator(int identifier, const std::string & name) :
    Operator(identifier, name)
{}

///////////////////////////////////////////////////////////////////////////////
// class AddOperator : public BinaryOperator                                 //
///////////////////////////////////////////////////////////////////////////////

AddOperator::AddOperator() :
    BinaryOperator(SID::OP_ADD, "+")
{}

double AddOperator::eval(double left_operand, double right_operand) const
{
    return left_operand + right_operand;
}

///////////////////////////////////////////////////////////////////////////////
// class SubOperator : public BinaryOperator                                 //
///////////////////////////////////////////////////////////////////////////////

SubOperator::SubOperator() :
    BinaryOperator(SID::OP_SUB, "-")
{}

double SubOperator::eval(double left_operand, double right_operand) const
{
    return left_operand - right_operand;
}

///////////////////////////////////////////////////////////////////////////////
// class MulOperator : public BinaryOperator                                 //
///////////////////////////////////////////////////////////////////////////////

MulOperator::MulOperator() :
    BinaryOperator(SID::OP_MUL, "*")
{}

double MulOperator::eval(double left_operand, double right_operand) const
{
    return left_operand * right_operand;
}

///////////////////////////////////////////////////////////////////////////////
// class DivOperator : public BinaryOperator                                 //
///////////////////////////////////////////////////////////////////////////////

DivOperator::DivOperator() :
    BinaryOperator(SID::OP_DIV, "/")
{}

double DivOperator::eval(double left_operand, double right_operand) const
{
    return left_operand / right_operand;
}

///////////////////////////////////////////////////////////////////////////////
// class AtomicValue                                                         //
///////////////////////////////////////////////////////////////////////////////

AtomicValue::AtomicValue(int identifier) :
    Symbol(identifier, true)
{}

///////////////////////////////////////////////////////////////////////////////
// class Number : public AtomicValue                                         //
///////////////////////////////////////////////////////////////////////////////

Number::Number(double value) :
    AtomicValue(SID::NUM),
    m_value(value)
{}

std::string Number::text() const
{
    std::string value_str;
    std::stringstream stream;
    stream << m_value;
    stream >> value_str;
    return value_str;
}

double Number::eval(const std::map<std::string, double> & values) const
{
    UNUSED_PARAMETER(values);
    return m_value;
}

///////////////////////////////////////////////////////////////////////////////
// class Variable : public AtomicValue                                       //
///////////////////////////////////////////////////////////////////////////////

Variable::Variable(const std::string & name) :
    AtomicValue(SID::VAR),
    m_name(name)
{}

std::string Variable::text() const
{
    return m_name;
}

double Variable::eval(const std::map<std::string, double> & values) const
{
    return values.at(m_name);
}

///////////////////////////////////////////////////////////////////////////////
// class Expression : public Symbol                                          //
///////////////////////////////////////////////////////////////////////////////

Expression::Expression() :
    Symbol(SID::EXP, false)
{}

///////////////////////////////////////////////////////////////////////////////
// class AtomicExpression : public Expression                                //
///////////////////////////////////////////////////////////////////////////////

AtomicExpression::AtomicExpression(std::unique_ptr<const AtomicValue> atomic_value) :
    m_atomic_value(std::move(atomic_value))
{}

std::string AtomicExpression::text() const
{
    return m_atomic_value->text();
}

double AtomicExpression::eval(const std::map<std::string, double> & values) const
{
    return m_atomic_value->eval(values);
}

///////////////////////////////////////////////////////////////////////////////
// class BinaryExpression : public Expression                                //
///////////////////////////////////////////////////////////////////////////////

BinaryExpression::BinaryExpression(
        std::unique_ptr<const Expression> left_operand,
        std::unique_ptr<const Expression> right_operand,
        std::unique_ptr<const BinaryOperator> binary_operator) :
    m_left_operand(std::move(left_operand)),
    m_right_operand(std::move(right_operand)),
    m_binary_operator(std::move(binary_operator))
{}

std::string BinaryExpression::text() const
{
    return m_left_operand->text() + m_binary_operator->text() + m_right_operand->text();
}

double BinaryExpression::eval(const std::map<std::string, double> & values) const
{
    return m_binary_operator->eval(m_left_operand->eval(values), m_right_operand->eval(values));
}

///////////////////////////////////////////////////////////////////////////////
// class BracketedExpression : public Expression                             //
///////////////////////////////////////////////////////////////////////////////

BracketedExpression::BracketedExpression(
        std::unique_ptr<const Expression> inner_expression,
        std::unique_ptr<const OpenBracket> left_bracket,
        std::unique_ptr<const ClosedBracket> right_bracket) :
    m_inner_expression(std::move(inner_expression)),
    m_left_bracket(std::move(left_bracket)),
    m_right_bracket(std::move(right_bracket))
{}

std::string BracketedExpression::text() const
{
    return m_left_bracket->text() + m_inner_expression->text() + m_right_bracket->text();
}

double BracketedExpression::eval(const std::map<std::string, double> & values) const
{
    return m_inner_expression->eval(values);
}

///////////////////////////////////////////////////////////////////////////////
// class Axiom : public Symbol                                               //
///////////////////////////////////////////////////////////////////////////////

Axiom::Axiom(std::unique_ptr<const Expression> expression) :
    Symbol(SID::AXIOM, false),
    m_expression(std::move(expression))
{}

std::string Axiom::text() const
{
    return m_expression->text();
}

double Axiom::eval(const std::map<std::string, double> & values) const
{
    return m_expression->eval(values);
}
