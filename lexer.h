#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

// --------------------------------------------------------- C++ System Headers
#include <memory>
#include <string>

// ------------------------------------------------------------ Project Headers
#include "symbols.h"

///////////////////////////////////////////////////////////////////////////////
// class Lexer                                                               //
///////////////////////////////////////////////////////////////////////////////

class Lexer
{
public:
    // ----------------------------------------------- Constructor
    Lexer(const std::string & expression);

    // ------------------------------------------------ Public Member Functions
    std::unique_ptr<const Symbol> top() const;
    std::unique_ptr<const Symbol> pop();

private:
    std::string m_expression;
    
    // ----------------------------------------------- Private Member Functions
    std::string next_token() const;
    std::unique_ptr<const Symbol> allocate_symbol(const std::string & token) const;
};

#endif // LEXER_H_INCLUDED
