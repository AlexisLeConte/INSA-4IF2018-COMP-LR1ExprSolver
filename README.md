# LR1 Expression Solver

A simple finite state machine arithmetic expression solver based on a LR(1) grammar.

### Features

* Supports floating point numbers
* Supports binary arithmetic operators `+`, `-`, `*`, `/`
* Supports parentheses
* Supports named variables

### Usage Example

`./LR1ExprSolver "(a+b)*5" a 2.5 b 3` will compute (2.5+3)*5 = 27.5

### How to Build with CMake

```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .

```

