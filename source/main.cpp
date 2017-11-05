#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <stack>
#define varepsilon 'e'

// 0 подразумевается initial state всегда
class CAutomata {
public:

    // Простой конструктор для автомата задающего язык из одной буквы
    explicit CAutomata(char symbol);

    // Конструктор для сложения или конъюнкции
    CAutomata(CAutomata *first, CAutomata *second, char operation);

    // Конструктор для звезды клини
    CAutomata(CAutomata *old_automata, char operation);

    void PrintAutomata() {
        std::cout << "\n\nInitial state is 0, terminal vertice is in {}\n- - - - - - - - -";
        for (size_t i = 0; i < states_count; i++) {
            for (size_t j = 0; j < states_count; j++) {
                char current_symbol = edges_matrix[i][j];
                if ((int) current_symbol != 0) {
                    if (current_symbol != varepsilon) {
                        if (accepting_states.count(j)) {
                            std::cout << "\n" << i << " --" << current_symbol << "--> {" << j << "}";
                        } else {
                            std::cout << "\n" << i << " --" << current_symbol << "--> ." << j << ".";
                        }
                    } else {
                        if (accepting_states.count(j)) {
                            std::cout << "\n" << i << " -----> {" << j << "}";
                        } else {
                            std::cout << "\n" << i << " -----> ." << j << ".";
                        }
                    }
                }
            }
        }
        std::cout << "\n-~-~-~-~-~-~-~-~-";
    }

protected:
    // Матрица n*n наборов (множеств) символов
    // Множество символов в [i][j] ячейке соответствует
    // множеству символов на ребре из i в j вершину
    // Напр.: a,b,varepsilon соответствует ребру a+b+\varepsilon
    std::vector<std::vector<char>> edges_matrix;
    std::set<size_t> accepting_states;
    size_t states_count;
};

CAutomata::CAutomata(char symbol) {
    assert(symbol == 'a' || symbol == 'b' || symbol == 'c' || symbol == '1');
    // Случай автомата получаемого из символа '1'
    // Он состоит из единственного состояния
    // которое одновременно начальное и конечное
    if (symbol == '1') {
        states_count=1;

        edges_matrix.resize(states_count);
        edges_matrix[0].resize(states_count);

        accepting_states.insert(0);
    }
    // Случай автомата получаемого из буквы 'a', 'b', 'c'
    // Состояний у нас 2, начальное и конечное
    // Есть ребро с данным символом из начального в конечное
    else {
        states_count=2;

        edges_matrix.resize(states_count);
        for (auto&& i : edges_matrix) i.resize(states_count);
        edges_matrix[0][1] = symbol;

        accepting_states.insert(1);
    }
}

CAutomata::CAutomata(CAutomata *first, CAutomata *second, char operation) {
    assert(operation == '.' || operation == '+');
    switch (operation) {
        case '+': {
            // Состояний всего состояний в первом автомате, во втором
            // плюс новое начальное состояние
            states_count = 1 + first->states_count + second->states_count;
            edges_matrix.resize(states_count);
            for (auto &&i: edges_matrix) i.resize(states_count);
            // Начинаем заполнять матрицу графа ребрами первого автомата
            // Начальное состояние первого автомата лежит в offset (1)
            int offset = 1;
            // eps-ребро из нового начального в прежнее начального первого
            edges_matrix[0][offset] = varepsilon;
            for (size_t i = 0; i < first->states_count; i++) {
                for (size_t j = 0; j < first->states_count; j++) {
                    edges_matrix[i + offset][j + offset] = first->edges_matrix[i][j];
                }
            }
            for (size_t v : first->accepting_states) {
                accepting_states.insert(v + offset);
            }
            // Начинаем заполнять матрицу графа ребрами второго автомат
            // Начальное состояние вторго автомата лежит в offset (1 + first->states_count)
            offset += first->states_count;
            // eps-ребро из нового начального в прежнее начального второго
            edges_matrix[0][offset] = varepsilon;
            for (size_t i = 0; i < second->states_count; i++) {
                for (size_t j = 0; j < second->states_count; j++) {
                    edges_matrix[i + offset][j + offset] = second->edges_matrix[i][j];
                }
            }
            for (size_t v : second->accepting_states) {
                accepting_states.insert(v + offset);
            }
            break;
        }
        case '.': {
            // Состояний всего состояний в первом автомате + во втором
            states_count = first->states_count + second->states_count;
            edges_matrix.resize(states_count);
            for (auto &&i: edges_matrix) i.resize(states_count);
            // Начинаем заполнять матрицу графа ребрами первого автомата
            // Начальное состояние первого автомата станет новым начальным состоянием
            int offset = 0;
            // Копируем ребра из первого
            for (size_t i = 0; i < first->states_count; ++i) {
                for (size_t j = 0; j < first->states_count; ++j) {
                    edges_matrix[i + offset][j + offset] = first->edges_matrix[i][j];
                }
            }
            // Начинаем заполнять матрицу графа ребрами второго автомата
            offset += first->states_count;
            // Копируем ребра из второго
            for (size_t i = 0; i < second->states_count; ++i) {
                for (size_t j = 0; j < second->states_count; ++j) {
                    edges_matrix[i + offset][j + offset] = second->edges_matrix[i][j];
                }
            }
            // Добавляем eps-рёбра из терминальных ранее вершин первого автомата
            // в начальное ранее состояние второго автомата
            for (size_t v : first->accepting_states) {
                edges_matrix[v][offset] = varepsilon;
            }
            // Дозаполнили терминальные вершинами терминалами второго
            for (size_t v : second->accepting_states) {
                accepting_states.insert(v + offset);
            }
            break;
        }
    }
}

CAutomata::CAutomata(CAutomata *old_automata, char operation) {
    assert (operation == '*');
    // Состояний всего состояний в прежнем автомате + 1
    states_count = old_automata->states_count + 1;
    edges_matrix.resize(states_count);
    for (auto &&i: edges_matrix) i.resize(states_count);
    // Начинаем заполнять матрицу графа ребрами прежнего автомата
    int offset = 1;
    // Копируем ребра из прежнего
    for (size_t i = 0; i < old_automata->states_count; ++i) {
        for (size_t j = 0; j < old_automata->states_count; ++j) {
            edges_matrix[i + offset][j + offset] = old_automata->edges_matrix[i][j];
        }
    }
    // Добавляем eps-ребро из нового начального в прежнее начальное
    edges_matrix[0][1] = varepsilon;
    // Добавляем eps-рёбра из терминальных ранее вершин прежнего автомата
    // в новое начальное состояние автомата
    for (size_t v : old_automata->accepting_states) {
        edges_matrix[offset + v][0] = varepsilon;
    }
    // Единственное конечное состояние нового автомата будет
    // его начальное состояние
    accepting_states.insert(0);

}

namespace MyTests {

// tests for '1'
    void runTest1() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '1'\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('1');
        whatever0.PrintAutomata();

    }

// tests for '+'
// regular expression: "a+b+c"
// regular exp in RPN: "ab+c+"
    void runTest2() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '+'\n";
        std::cout << "regular expression: \"a+b+c\"\n";
        std::cout << "regular exp in RPN: \"ab+c+\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');;
        whatever0.PrintAutomata();

        CAutomata whatever1('b');
        whatever1.PrintAutomata();

        CAutomata whatever2(&whatever0, &whatever1, '+');
        whatever2.PrintAutomata();

        CAutomata whatever3('c');
        whatever3.PrintAutomata();

        CAutomata whatever4(&whatever2, &whatever3, '+');
        whatever4.PrintAutomata();

    }

// tests for '.'
// regular expression: "a.b.c"
// regular exp in RPN: "ab.c."
    void runTest3() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '.'\n";
        std::cout << "regular expression: \"a.b.c\"\n";
        std::cout << "regular exp in RPN: \"ab.c.\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');
        whatever0.PrintAutomata();

        CAutomata whatever1('b');
        whatever1.PrintAutomata();

        CAutomata whatever2(&whatever0, &whatever1, '.');
        whatever2.PrintAutomata();

        CAutomata whatever3('c');
        whatever3.PrintAutomata();

        CAutomata whatever4(&whatever2, &whatever3, '.');
        whatever4.PrintAutomata();
    }

// tests for '+ . +'
// regular expression: "(a+b).c+a"
// regular exp in RPN: "ab+c.a+"
    void runTest4() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '+ . +'\n";
        std::cout << "regular expression: \"(a+b).c+a\"\n";
        std::cout << "regular exp in RPN: \"ab+c.a+\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');
        whatever0.PrintAutomata();

        CAutomata whatever1('b');
        whatever1.PrintAutomata();

        CAutomata whatever2(&whatever0, &whatever1, '+');
        whatever2.PrintAutomata();

        CAutomata whatever3('c');
        whatever3.PrintAutomata();

        CAutomata whatever4(&whatever2, &whatever3, '.');
        whatever4.PrintAutomata();

        CAutomata whatever5('a');
        whatever5.PrintAutomata();

        CAutomata whatever6(&whatever4, &whatever5, '+');
        whatever6.PrintAutomata();

    }

// tests for '*'
// regular expression: "a*"
// regular exp in RPN: "a*"
    void runTest5() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '*'\n";
        std::cout << "regular expression: \"a*\"\n";
        std::cout << "regular exp in RPN: \"a*\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');
        whatever0.PrintAutomata();

        CAutomata whatever1(&whatever0, '*');
        whatever1.PrintAutomata();

    }

// tests for '+ . *'
// regular expression: "((a+b).c)*"
// regular exp in RPN: "ab+c.*"
    void runTest6() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '+ . +'\n";
        std::cout << "regular expression: \"((a+b).c)*\"\n";
        std::cout << "regular exp in RPN: \"ab+c.*\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');
        whatever0.PrintAutomata();

        CAutomata whatever1('b');
        whatever1.PrintAutomata();

        CAutomata whatever2(&whatever0, &whatever1, '+');
        whatever2.PrintAutomata();

        CAutomata whatever3('c');
        whatever3.PrintAutomata();

        CAutomata whatever4(&whatever2, &whatever3, '.');
        whatever4.PrintAutomata();

        CAutomata whatever6(&whatever4, '*');
        whatever6.PrintAutomata();

    }

    void runTests() {

        bool on = true;

        while (on) {
            std::cout << "\n\n";
            int option;
            std::cin >> option;
            switch (option) {
                case -1: {
                    std::cout << "\n1 for '1'";
                    std::cout << "\n2 for '+'";
                    std::cout << "\n3 for '.'";
                    std::cout << "\n4 for '+ . +'";
                    std::cout << "\n5 for '*'";
                    std::cout << "\n6 for '+ . *'";
                    break;
                }
                case 0: {
                    for (int i = 0; i < 4; ++i) std::cout << "\n\n\n\n";
                    break;
                }
                case 1: {
                    runTest1();
                    break;
                }
                case 2: {
                    runTest2();
                    break;
                }
                case 3: {
                    runTest3();
                    break;
                }
                case 4: {
                    runTest4();
                    break;
                }
                case 5: {
                    runTest5();
                    break;
                }
                case 6: {
                    runTest6();
                    break;
                }
                default: {
                    on = false;
                }
            }
        }
    }
}

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

    std::string some_expression_in_rpn;
    std::cin >> some_expression_in_rpn;
    CAutomata automata_from_expression = ParseExpression(some_expression_in_rpn);
    automata_from_expression.PrintAutomata();

}