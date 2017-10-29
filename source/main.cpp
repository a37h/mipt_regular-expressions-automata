#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#define varepsilon 'e'

int main() {
    std::cout << varepsilon;
    CAutomata whatever('a');

    return 0;
}

// 0 подразумевается initial state всегда
class CAutomata {
public:
//    size_t getStatesCount() { return states_count; };

    // Простой конструктор для автомата задающего язык из одной буквы
    explicit CAutomata(char symbol);

    // Конструктор для сложения, конъюнкции или звезды клини
    CAutomata::CAutomata(CAutomata *first, CAutomata *second, char operation);


protected:
    // Матрица n*n наборов (множеств) символов
    // Множество символов в [i][j] ячейке соответствует
    // множеству символов на ребре из i в j вершину
    // Напр.: a,b,varepsilon соответствует ребру a+b+\varepsilon
    std::vector<std::vector<std::set<char>>> edges_matrix;
    std::set<int> accepting_states;
    size_t states_count;
};

explicit CAutomata::CAutomata(char symbol) {
    if (symbol == '1') {
        states_count=1;
        // Заполняем матрицу графа
        edges_matrix.resize(states_count);
        edges_matrix[0].resize(states_count);
        // Добавляем терминальные вершины
        accepting_states.insert(0);
    } else {
        assert(symbol == 'a' || symbol == 'b' || symbol == 'c');
        states_count=2;
        // Заполняем матрицу графа
        edges_matrix.resize(states_count);
        for (auto&& i : edges_matrix) i.resize(states_count);
        edges_matrix[0][1].insert(symbol);
        // Добавляем терминальные вершины
        accepting_states.insert(1);
    }
}

CAutomata::CAutomata(CAutomata *first, CAutomata *second, char operation) {
    switch (operation) {
        case '+': {
            // Подготовили матрицу графа
            states_count = 1 + first->states_count + second->states_count;
            edges_matrix.resize(states_count);
            for (auto &&i: edges_matrix) i.resize(states_count);
            // Начинаем заполнять матрицу графа ребрами первого автомата
            int offset = 1;
            edges_matrix[0][offset].insert(varepsilon);
            for (int i = 0; i < first->states_count; i++) {
                for (int j = 0; j < first->states_count; j++) {
                    for (char v : first->edges_matrix[i][j]) {
                        edges_matrix[i + offset][j + offset].insert(v);
                    }
                }
            }
            for (int v : first->accepting_states) {
                accepting_states.insert(v + offset);
            }
            // Начинаем заполнять матрицу графа ребрами второго автомата
            offset += first->states_count;
            edges_matrix[0][offset].insert(varepsilon);
            for (int i = 0; i < second->states_count; i++) {
                for (int j = 0; j < second->states_count; j++) {
                    for (char v : second->edges_matrix[i][j]) {
                        edges_matrix[i + offset][j + offset].insert(v);
                    }
                }
            }
            for (int v : second->accepting_states) {
                accepting_states.insert(v + offset);
            }
        }

        case '.': {

        }

        default: {
            assert(operation == '+' || operation == '.' || operation == '*');
        }
    }
}