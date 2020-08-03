// --------------------------------------------------------- C++ System Headers
#include <iostream>
#include <map>
#include <memory>

// ------------------------------------------------------------ Project Headers
#include "fsm.h"
#include "lexer.h"
#include "symbols.h"

///////////////////////////////////////////////////////////////////////////////
// Driver program                                                            //
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    if(argc < 2 || argc%2 != 0)
    {
        std::cout << "Usage: ./LR1 ARITHMETIC_EXPRESSION [VAR_NAME VAR_VALUE]*" << std::endl;
        return -1;
    }

    std::map<std::string, double> values;
    for(int i=2; i<argc; i+=2)
    {
        values[argv[i]] = std::atof(argv[i+1]);
    }

    Lexer lexer(argv[1]);
    FiniteStateMachine fsm(lexer);
    std::unique_ptr<const Axiom> a = fsm.analyze();
    if(a.get() != nullptr)
    {
        std::cout << a->text() << " = " << a->eval(values) << std::endl;
    }
    else
    {
        std::cout << "Invalid arithmetic expression!" << std::endl;
    }
    return 0;
}
