#include <iostream>
#include "CSolver/csolver.h"

int main() {

    std::string some_expression_in_rpn;
    std::cin >> some_expression_in_rpn;
    CSolver solver(&some_expression_in_rpn);
    solver.ShowAutomata();

}