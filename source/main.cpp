#include <iostream>
#include "CAutomata/cautomata.h"
#include "CAutomata/Tests/CAutomataTests.h"

CAutomata ParseExpression (std::string& expression) {
    // Стек для хранения промежуточных автоматов, создаваемых по мере вычитывания регулярки
    std::stack<CAutomata> AutomataStack;
    for (char symbol : expression) {
        switch (symbol) {
            case 'a': case 'b': case 'c': {
                AutomataStack.push(CAutomata(symbol));
                break;
            }
            case '+': case '.': {
                if (AutomataStack.size() >= 2) {
                    CAutomata temp1 = AutomataStack.top();
                    AutomataStack.pop();
                    CAutomata temp2 = AutomataStack.top();
                    AutomataStack.pop();
                    AutomataStack.push(CAutomata(&temp1,&temp2,symbol));
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
                    AutomataStack.push(CAutomata(&temp,symbol));
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
        return AutomataStack.top();
    } else {
        std::cout << "ERROR";
        exit(4);
    }
}

int main() {
    //CAutomataTests::runTests();

    std::string some_expression_in_rpn;
    std::cin >> some_expression_in_rpn;
    CAutomata automata_from_expression = ParseExpression(some_expression_in_rpn);
    automata_from_expression.PrintAutomata();

}