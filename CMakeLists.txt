cmake_minimum_required (VERSION 3.8)
project (LR1ExprSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable (LR1ExprSolver fsm.h fsm.cpp lexer.h lexer.cpp symbols.h symbols.cpp main.cpp)

