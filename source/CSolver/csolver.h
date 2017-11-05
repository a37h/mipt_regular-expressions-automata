//
// Created by qua on 05.11.17.
//

#ifndef SOURCE_CSOLVER_H
#define SOURCE_CSOLVER_H

#include "../CAutomata/cautomata.h"
#include "CRotation/crotation.h"
#include <stack>
#include <queue>

class CSolver {
public:

    explicit CSolver(std::string *expression_, char symbolX, int prefLengthK);
    void ParseExpression();
    void ShowAutomata();
    void CustomDFS();
    void CustomBFS(CRotation initialrotation);

private:

    CAutomata automata;
    std::vector<int> shadesOfGrey;
    std::string *expression;
    char symbolX;
    int prefLengthK;
    int min_length = -1;

};

#endif //SOURCE_CSOLVER_H