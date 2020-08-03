// --------------------------------------------------------- C++ System Headers
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>

// ------------------------------------------------------------ Project Headers
#include "fsm.h"
#include "lexer.h"
#include "symbols.h"

#define UNUSED_PARAMETER(X) (void)(X) // Ignore "unused parameter" warnings

///////////////////////////////////////////////////////////////////////////////
// class FiniteStateMachine                                                  //
///////////////////////////////////////////////////////////////////////////////

FiniteStateMachine::FiniteStateMachine(const Lexer & lexer) :
    m_lexer(lexer),
    m_fatal_error(false)
{}

std::unique_ptr<const Axiom> FiniteStateMachine::analyze()
{
    m_states.push(std::make_unique<const State1>());
    while(!m_fatal_error)
    {
        std::unique_ptr<const Symbol> next = std::move(m_lexer.top());
        if(next.get() == nullptr)
        {
            return std::unique_ptr<const Axiom>();
        }
        if(m_states.top()->transition(*this, std::move(next)))
        {
            return std::unique_ptr<const Axiom>((const Axiom*) m_symbols.top().release());
        }
    }
    return std::unique_ptr<const Axiom>();
}

std::unique_ptr<const Symbol> FiniteStateMachine::pop_symbol()
{
    std::unique_ptr<const Symbol> symbol = std::move(m_symbols.top());
    m_symbols.pop();
    return symbol;
}

void FiniteStateMachine::shift(
        std::unique_ptr<const State> state,
        std::unique_ptr<const Symbol> symbol)
{
    if(symbol->terminal())
    {
        m_lexer.pop();
    }
    m_states.push(std::move(state));
    m_symbols.push(std::move(symbol));
}

void FiniteStateMachine::reduce(size_t n, std::unique_ptr<const Symbol> symbol)
{
    for(size_t i=0; i<n; ++i)
    {
        m_states.pop();
    }
    m_states.top()->transition(*this, std::move(symbol));
}

void FiniteStateMachine::error(bool fatal_error)
{
    std::cerr << "[Error] Unexpected token '" << m_lexer.top()->text();
    std::cerr << "' was discarded" << std::endl;
    if(fatal_error)
    {
        std::cerr << "[Error] Fatal error: analysis terminated" << std::endl;
        m_fatal_error = true;
    }
    m_lexer.pop();
}

///////////////////////////////////////////////////////////////////////////////
// States Transitions                                                        //
///////////////////////////////////////////////////////////////////////////////

bool State1::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::EXP:
            fsm.shift(std::make_unique<const State2>(), std::move(symbol));
            return false;
        case SID::OPEN_BRACKET:
            fsm.shift(std::make_unique<const State7>(), std::move(symbol));
            return false;
        case SID::VAR:
            fsm.shift(std::make_unique<const State6>(), std::move(symbol));
            return false;
        case SID::NUM:
            fsm.shift(std::make_unique<const State5>(), std::move(symbol));
            return false;
        case SID::AXIOM:
            fsm.shift(std::make_unique<const Accept>(), std::move(symbol));
            return true; // Success
    }
    fsm.error();
    return false;
}

bool State2::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::OP_ADD:
            fsm.shift(std::make_unique<const State3>(), std::move(symbol));
            return false;
        case SID::OP_SUB:
            fsm.shift(std::make_unique<const State11>(), std::move(symbol));
            return false;
        case SID::OP_MUL:
            fsm.shift(std::make_unique<const State10>(), std::move(symbol));
            return false;
        case SID::OP_DIV:
            fsm.shift(std::make_unique<const State12>(), std::move(symbol));
            return false;
        case SID::END_OF_STREAM:
        {
            std::unique_ptr<const Expression> expr((Expression*) fsm.pop_symbol().release());
            fsm.reduce(1, std::make_unique<Axiom>(std::move(expr)));
            return false;
        }
    }
    fsm.error();
    return false;
}

bool State3::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::VAR:
            fsm.shift(std::make_unique<const State6>(), std::move(symbol));
            return false;
        case SID::NUM:
            fsm.shift(std::make_unique<const State5>(), std::move(symbol));
            return false;
        case SID::OPEN_BRACKET:
            fsm.shift(std::make_unique<const State7>(), std::move(symbol));
            return false;
        case SID::EXP:
            fsm.shift(std::make_unique<const State4>(), std::move(symbol));
            return false;
    }
    fsm.error();
    return false;
}

bool State4::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::OP_MUL:
            fsm.shift(std::make_unique<const State10>(), std::move(symbol));
            return false;
        case SID::OP_DIV:
            fsm.shift(std::make_unique<const State12>(), std::move(symbol));
            return false;
    }
    std::unique_ptr<const Expression> right((Expression*) fsm.pop_symbol().release());
    std::unique_ptr<const BinaryOperator> op((BinaryOperator*) fsm.pop_symbol().release());
    std::unique_ptr<const Expression> left((Expression*) fsm.pop_symbol().release());
    fsm.reduce(3, std::make_unique<const BinaryExpression>(std::move(left), std::move(right), std::move(op)));
    return false;
}

bool State5::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    UNUSED_PARAMETER(symbol);
    std::unique_ptr<const AtomicValue> num((AtomicValue*) fsm.pop_symbol().release());
    fsm.reduce(1, std::make_unique<const AtomicExpression>(std::move(num)));
    return false;
}

bool State6::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    UNUSED_PARAMETER(symbol);
    std::unique_ptr<const AtomicValue> var((AtomicValue*) fsm.pop_symbol().release());
    fsm.reduce(1, std::make_unique<const AtomicExpression>(std::move(var)));
    return false;
}

bool State7::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::VAR:
            fsm.shift(std::make_unique<const State6>(), std::move(symbol));
            return false;
        case SID::NUM:
            fsm.shift(std::make_unique<const State5>(), std::move(symbol));
            return false;
        case SID::OPEN_BRACKET:
            fsm.shift(std::make_unique<const State7>(), std::move(symbol));
            return false;
        case SID::EXP:
            fsm.shift(std::make_unique<const State8>(), std::move(symbol));
            return false;    
    }
    fsm.error();
    return false;
}

bool State8::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::OP_ADD:
            fsm.shift(std::make_unique<const State3>(), std::move(symbol));
            return false;
        case SID::OP_SUB:
            fsm.shift(std::make_unique<const State11>(), std::move(symbol));
            return false;
        case SID::OP_MUL:
            fsm.shift(std::make_unique<const State10>(), std::move(symbol));
            return false;
        case SID::OP_DIV:
            fsm.shift(std::make_unique<const State12>(), std::move(symbol));
            return false;
        case SID::CLOSED_BRACKET:
            fsm.shift(std::make_unique<const State9>(), std::move(symbol));
            return false;
    }
    fsm.error();
    return false;
}

bool State9::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    UNUSED_PARAMETER(symbol);
    std::unique_ptr<const ClosedBracket> closed_bracket((ClosedBracket*) fsm.pop_symbol().release());
    std::unique_ptr<const Expression> expr((Expression*) fsm.pop_symbol().release());
    std::unique_ptr<const OpenBracket> open_bracket((OpenBracket*) fsm.pop_symbol().release());
    fsm.reduce(3, std::make_unique<const BracketedExpression>(std::move(expr), std::move(open_bracket), std::move(closed_bracket)));
    return false;
}

bool State10::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::VAR:
            fsm.shift(std::make_unique<const State6>(), std::move(symbol));
            return false;
        case SID::NUM:
            fsm.shift(std::make_unique<const State5>(), std::move(symbol));
            return false;
        case SID::OPEN_BRACKET:
            fsm.shift(std::make_unique<const State7>(), std::move(symbol));
            return false;
        case SID::EXP:
            fsm.shift(std::make_unique<const State15>(), std::move(symbol));
            return false;
    }
    fsm.error();
    return false;
}

bool State11::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::VAR:
            fsm.shift(std::make_unique<const State6>(), std::move(symbol));
            return false;
        case SID::NUM:
            fsm.shift(std::make_unique<const State5>(), std::move(symbol));
            return false;
        case SID::OPEN_BRACKET:
            fsm.shift(std::make_unique<const State7>(), std::move(symbol));
            return false;
        case SID::EXP:
            fsm.shift(std::make_unique<const State14>(), std::move(symbol));
            return false;
    }
    fsm.error();
    return false;
}

bool State12::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::VAR:
            fsm.shift(std::make_unique<const State6>(), std::move(symbol));
            return false;
        case SID::NUM:
            fsm.shift(std::make_unique<const State5>(), std::move(symbol));
            return false;
        case SID::OPEN_BRACKET:
            fsm.shift(std::make_unique<const State7>(), std::move(symbol));
            return false;
        case SID::EXP:
            fsm.shift(std::make_unique<const State13>(), std::move(symbol));
            return false;
    }
    fsm.error();
    return false;
}

bool State13::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    UNUSED_PARAMETER(symbol);
    std::unique_ptr<const Expression> right((Expression*) fsm.pop_symbol().release());
    std::unique_ptr<const BinaryOperator> op((BinaryOperator*) fsm.pop_symbol().release());
    std::unique_ptr<const Expression> left((Expression*) fsm.pop_symbol().release());
    fsm.reduce(3, std::make_unique<const BinaryExpression>(std::move(left), std::move(right), std::move(op)));
    return false;
}

bool State14::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    switch(*symbol)
    {
        case SID::OP_MUL:
            fsm.shift(std::make_unique<const State10>(), std::move(symbol));
            return false;
        case SID::OP_DIV:
            fsm.shift(std::make_unique<const State12>(), std::move(symbol));
            return false;
    }
    std::unique_ptr<const Expression> right((Expression*) fsm.pop_symbol().release());
    std::unique_ptr<const BinaryOperator> op((BinaryOperator*) fsm.pop_symbol().release());
    std::unique_ptr<const Expression> left((Expression*) fsm.pop_symbol().release());
    fsm.reduce(3, std::make_unique<const BinaryExpression>(std::move(left), std::move(right), std::move(op)));
    return false;
}

bool State15::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    UNUSED_PARAMETER(symbol);
    std::unique_ptr<const Expression> right((Expression*) fsm.pop_symbol().release());
    std::unique_ptr<const BinaryOperator> op((BinaryOperator*) fsm.pop_symbol().release());
    std::unique_ptr<const Expression> left((Expression*) fsm.pop_symbol().release());
    fsm.reduce(3, std::make_unique<const BinaryExpression>(std::move(left), std::move(right), std::move(op)));
    return false;
}

bool Accept::transition(
        FiniteStateMachine & fsm,
        std::unique_ptr<const Symbol> symbol) const
{
    UNUSED_PARAMETER(fsm);
    UNUSED_PARAMETER(symbol);
    return true;
}
