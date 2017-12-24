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
//    ShowAutomata();
    shadesOfGrey.resize(automata.GetSize(),prefLengthK_);
    CustomDFS();
    if (min_length == -1) {
        std::cout << "INF";
    } else {
        std::cout << min_length;
    }
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
                    AutomataStack.push(CAutomata(&temp2, &temp1, symbol));
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
        if (v.second == varepsilon){
            CRotation temp(v.first, 0);
            DFSStack.push(temp);
        } else if (v.second == symbolX) {
            CRotation temp(v.first, 1);
            DFSStack.push(temp);
        }
    }

    while (!DFSStack.empty()) {
        CRotation currentRotation = DFSStack.top();
        DFSStack.pop();


        if (shadesOfGrey[currentRotation.vertice] > 0) {

            for (std::pair<size_t,char> v : automata.GetNextVerts(currentRotation.vertice)) {
                if (v.second == varepsilon) {
                    DFSStack.push(CRotation(v.first, currentRotation.preflength));
                } else if (v.second == symbolX) {
                    DFSStack.push(CRotation(v.first, currentRotation.preflength+1));
                }
            }
        }

        shadesOfGrey[currentRotation.vertice] = shadesOfGrey[currentRotation.vertice] - 1;

        if (currentRotation.preflength == prefLengthK) {
            CustomBFS(currentRotation);
        }
    }
}

void CSolver::CustomBFS(CRotation initialrotation) {

    if (automata.isTerminal(initialrotation.vertice)) {
        if (initialrotation.preflength < min_length || min_length == -1) {
            min_length = (int) initialrotation.preflength;
        }
    }

    std::queue<CRotation> BFSQueue;

    std::vector<bool> UsedVerts(automata.GetSize(), false);

    for (std::pair<size_t,char> v : automata.GetNextVerts(initialrotation.vertice)) {
        if (v.second == varepsilon){
            CRotation temp(v.first, initialrotation.preflength);
            BFSQueue.push(temp);
        } else  {
            CRotation temp(v.first, initialrotation.preflength+1);
            BFSQueue.push(temp);
        }
    }

    while (!BFSQueue.empty()) {
        CRotation currentRotation = BFSQueue.front();
        BFSQueue.pop();

        if (!UsedVerts[currentRotation.vertice]) {
            for (std::pair<size_t,char> v : automata.GetNextVerts(currentRotation.vertice)) {
                if (v.second == varepsilon) {
                    BFSQueue.push(CRotation(v.first, currentRotation.preflength));
                } else {
                    BFSQueue.push(CRotation(v.first, currentRotation.preflength+1));
                }
            }
        }

        UsedVerts[currentRotation.vertice] = true;

        if (automata.isTerminal(currentRotation.vertice)) {
            if (currentRotation.preflength < min_length || min_length == -1) {
                min_length = (int) currentRotation.preflength;
            }
        }
    }
}