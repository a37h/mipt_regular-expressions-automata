//
// Created by qua on 05.11.17.
//

#include "csolver.h"

void CSolver::ShowAutomata() {
    automata.PrintAutomata();
}

CSolver::CSolver(std::string *expression_, char symbolX_, int prefLengthK_):
        expression(expression_),
        symbolX(symbolX_),
        prefLengthK(prefLengthK_),
        shadesOfGrey(0)
{
    ParseExpression();
    shadesOfGrey.resize(automata.GetSize(),prefLengthK_);
}

void CSolver::ParseExpression() {
// Стек для хранения промежуточных автоматов, создаваемых по мере вычитывания регулярки
    std::stack<CAutomata> AutomataStack;
    for (char symbol : *expression) {
        switch (symbol) {
            case 'a':
            case 'b':
            case 'c': {
                AutomataStack.push(CAutomata(symbol));
                break;
            }
            case '+':
            case '.': {
                if (AutomataStack.size() >= 2) {
                    CAutomata temp1 = AutomataStack.top();
                    AutomataStack.pop();
                    CAutomata temp2 = AutomataStack.top();
                    AutomataStack.pop();
                    AutomataStack.push(CAutomata(&temp1, &temp2, symbol));
                } else {
                    std::cout << "ERROR";
                    exit(1);
                }
                break;
            }
            case '*': {
                if (!AutomataStack.empty()) {
                    CAutomata temp = AutomataStack.top();
                    AutomataStack.pop();
                    AutomataStack.push(CAutomata(&temp, symbol));
                } else {
                    std::cout << "ERROR";
                    exit(2);
                }
                break;
            }
            default: {
                std::cout << "ERROR";
                exit(3);
            }
        }
    }
    if (AutomataStack.size() == 1) {
        automata = AutomataStack.top();
    } else {
        std::cout << "ERROR";
        exit(4);
    }
}

void CSolver::CustomDFS() {

    std::stack<CRotation> DFSStack;

    for (std::pair<size_t,char> v : automata.GetNextVerts(0)) {
        CRotation temp(v.first, v.second, 0);
        DFSStack.push(temp);
    }

    while (!DFSStack.empty()) {
        CRotation tempVertice = DFSStack.top();
        DFSStack.pop();


    }
}