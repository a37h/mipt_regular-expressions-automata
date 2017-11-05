#include <iostream>
#include "CSolver/csolver.h"

int main() {

    std::string some_expression_in_rpn;
    std::cin >> some_expression_in_rpn;
    char X;
    std::cin >> X;
    int deg;
    std::cin >> deg;

    CSolver solver(&some_expression_in_rpn, X, deg);

}