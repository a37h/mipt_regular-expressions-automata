#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#define varepsilon 'e'

// 0 подразумевается initial state всегда
class CAutomata {
public:
    //    size_t getStatesCount() { return states_count; };

    // Простой конструктор для автомата задающего язык из одной буквы
    explicit CAutomata(char symbol);

    // Конструктор для сложения, конъюнкции или звезды клини
    CAutomata(CAutomata *first, CAutomata *second, char operation);

    void PrintAutomata() {
        std::cout << "\n\nShowing automata:\n- - - - - - - - -";
        for (size_t i = 0; i < states_count; i++) {
            for (size_t j = 0; j < states_count; j++) {
                if ((int) edges_matrix[i][j] != 0)
                std::cout << "\n" << i << " --" << edges_matrix[i][j] << "--> " << j;
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
    std::set<int> accepting_states;
    size_t states_count;
};

CAutomata::CAutomata(char symbol) {
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
        assert(symbol == 'a' || symbol == 'b' || symbol == 'c');
        states_count=2;

        edges_matrix.resize(states_count);
        for (auto&& i : edges_matrix) i.resize(states_count);
        edges_matrix[0][1] = symbol;

        accepting_states.insert(1);
    }
}

CAutomata::CAutomata(CAutomata *first, CAutomata *second, char operation) {
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
            for (int i = 0; i < first->states_count; i++) {
                for (int j = 0; j < first->states_count; j++) {
                    edges_matrix[i + offset][j + offset] = first->edges_matrix[i][j];
                }
            }
            for (int v : first->accepting_states) {
                accepting_states.insert(v + offset);
            }
            // Начинаем заполнять матрицу графа ребрами второго автомат
            // Начальное состояние вторго автомата лежит в offset (1 + first->states_count)
            offset += first->states_count;
            // eps-ребро из нового начального в прежнее начального второго
            edges_matrix[0][offset] = varepsilon;
            for (int i = 0; i < second->states_count; i++) {
                for (int j = 0; j < second->states_count; j++) {
                    edges_matrix[i + offset][j + offset] = second->edges_matrix[i][j];
                }
            }
            for (int v : second->accepting_states) {
                accepting_states.insert(v + offset);
            }
        }

        case '.': {
            ;
        }

        default: {
            assert(operation == '+' || operation == '.' || operation == '*');
        }
    }
}

void runTest1();

int main() {
    std::cout << varepsilon;

//    runTest1();

    return 0;
}

// tests for '+'
void runTest1() {

    CAutomata whatever0('a');
    CAutomata whatever1('b');
    whatever0.PrintAutomata();
    whatever1.PrintAutomata();

    CAutomata whatever2(&whatever0,&whatever1,'+');
    whatever2.PrintAutomata();

    CAutomata whatever3('c');
    whatever3.PrintAutomata();

    CAutomata whatever4(&whatever2,&whatever3,'+');
    whatever4.PrintAutomata();

}