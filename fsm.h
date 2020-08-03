#ifndef FSM_H_INCLUDED
#define FSM_H_INCLUDED

// --------------------------------------------------------- C++ System Headers
#include <memory>
#include <stack>

// ------------------------------------------------------------ Project Headers
#include "lexer.h"
#include "symbols.h"

// ------------------------------------------------------- Forward Declarations
class State;

///////////////////////////////////////////////////////////////////////////////
// class FiniteStateMachine                                                  //
///////////////////////////////////////////////////////////////////////////////

class FiniteStateMachine
{
public:
    // ----------------------------------------------- Constructor / Destructor
    FiniteStateMachine(const Lexer & lexer);
    FiniteStateMachine(const FiniteStateMachine & source) = delete;

    // ------------------------------------------------ Public Member Functions
    std::unique_ptr<const Axiom> analyze();
    std::unique_ptr<const Symbol> pop_symbol();
    void shift(std::unique_ptr<const State> state, std::unique_ptr<const Symbol> symbol);
    void reduce(size_t n, std::unique_ptr<const Symbol> symbol);
    void error(bool fatal_error = true);

    // --------------------------------------------------- Overloaded Operators
    FiniteStateMachine & operator=(const FiniteStateMachine & source) = delete;
private:
    Lexer m_lexer;
    bool m_fatal_error;
    std::stack<std::unique_ptr<const State>> m_states;
    std::stack<std::unique_ptr<const Symbol>> m_symbols;
};

///////////////////////////////////////////////////////////////////////////////
// class State                                                               //
///////////////////////////////////////////////////////////////////////////////

class State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State() = default;
    virtual ~State() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const = 0;
};

///////////////////////////////////////////////////////////////////////////////
// class State1 : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class State1 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State1() = default;
    virtual ~State1() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State2 : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class State2 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State2() = default;
    virtual ~State2() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State3 : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class State3 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State3() = default;
    virtual ~State3() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State4 : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class State4 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State4() = default;
    virtual ~State4() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State5 : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class State5 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State5() = default;
    virtual ~State5() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State6 : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class State6 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State6() = default;
    virtual ~State6() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State7 : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class State7 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State7() = default;
    virtual ~State7() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State8 : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class State8 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State8() = default;
    virtual ~State8() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State9 : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class State9 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State9() = default;
    virtual ~State9() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State10 : public State                                              //
///////////////////////////////////////////////////////////////////////////////

class State10 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State10() = default;
    virtual ~State10() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State11 : public State                                              //
///////////////////////////////////////////////////////////////////////////////

class State11 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State11() = default;
    virtual ~State11() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State12 : public State                                              //
///////////////////////////////////////////////////////////////////////////////

class State12 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State12() = default;
    virtual ~State12() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State13 : public State                                              //
///////////////////////////////////////////////////////////////////////////////

class State13 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State13() = default;
    virtual ~State13() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State14 : public State                                              //
///////////////////////////////////////////////////////////////////////////////

class State14 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State14() = default;
    virtual ~State14() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class State15 : public State                                              //
///////////////////////////////////////////////////////////////////////////////

class State15 : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    State15() = default;
    virtual ~State15() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

///////////////////////////////////////////////////////////////////////////////
// class Accept : public State                                               //
///////////////////////////////////////////////////////////////////////////////

class Accept : public State
{
public:
    // ----------------------------------------------- Constructor / Destructor
    Accept() = default;
    virtual ~Accept() = default;

    // ------------------------------------------------ Public Member Functions
    virtual bool transition(
            FiniteStateMachine & fsm,
            std::unique_ptr<const Symbol> symbol) const override;
};

#endif // FSM_H_INCLUDED
