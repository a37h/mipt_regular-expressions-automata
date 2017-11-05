//
// Created by qua on 05.11.17.
//

#ifndef SOURCE_CSOLVER_H
#define SOURCE_CSOLVER_H

#include "../CAutomata/cautomata.h"

class CSolver {
public:

    explicit CSolver(std::string *expression_);
    void ParseExpression();
    void ShowAutomata();
    void CustomDFS();

private:

    CAutomata automata;
    std::string *expression;

};

#endif //SOURCE_CSOLVER_H
