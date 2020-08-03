// --------------------------------------------------------- C++ System Headers
#include <cctype>
#include <memory>
#include <string>

// ------------------------------------------------------------ Project Headers
#include "lexer.h"
#include "symbols.h"

///////////////////////////////////////////////////////////////////////////////
// class Lexer                                                               //
///////////////////////////////////////////////////////////////////////////////

Lexer::Lexer(const std::string & expression) :
    m_expression(expression)
{
    // remove leading and trailing whitespaces
    size_t leading = m_expression.find_first_not_of(" ");
    size_t trailing = m_expression.find_last_not_of(" ");
    if(leading != std::string::npos)
    {
        m_expression = m_expression.substr(leading, trailing - leading + 1);
    }
    else
    {
        m_expression.clear();
    }
}

std::unique_ptr<const Symbol> Lexer::top() const
{
    return allocate_symbol(next_token());
}

std::unique_ptr<const Symbol> Lexer::pop()
{
    std::string token = next_token();
    m_expression.erase(0, token.size());
    size_t whitespaces = m_expression.find_first_not_of(" ");
    m_expression.erase(0, whitespaces);
    return allocate_symbol(token);
}

std::string Lexer::next_token() const
{
    if(m_expression.empty())
    {
        return "";
    }
    char c = m_expression[0];

    // Variables & Numbers
    if(std::isalnum(c))
    {
        for(size_t i=1; i<m_expression.size(); ++i)
        {
            if(!(std::isalnum(m_expression[i]) || m_expression[i] == '.'))
            {
                return m_expression.substr(0, i);
            }
        }
        return m_expression;
    }

    // Operators
    return std::string(1, c);
}

std::unique_ptr<const Symbol> Lexer::allocate_symbol(const std::string & token) const
{
    if(token.empty())
    {
        return std::make_unique<const EndOfStream>();
    }
    char c = token[0];

    // Variables & Numbers
    if(std::isalpha(c))
    {
        return std::make_unique<const Variable>(token);
    }
    if(std::isdigit(c))
    {
        return std::make_unique<const Number>(std::stod(token));
    }

    // Operators
    switch(c)
    {
        case '+': return std::make_unique<const AddOperator>();
        case '-': return std::make_unique<const SubOperator>();
        case '*': return std::make_unique<const MulOperator>();
        case '/': return std::make_unique<const DivOperator>();
        case '(': return std::make_unique<const OpenBracket>();
        case ')': return std::make_unique<const ClosedBracket>();
    }

    // Error
    return std::unique_ptr<const Symbol>();
}
