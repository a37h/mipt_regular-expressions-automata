#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#define varepsilon 'e'

class CAutomata {
public:
    size_t getStatesCount() {states_count};
    // Простой конструктор для автомата задающего язык из одной буквы
    explicit CAutomata(char symbol) {
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
private:
    // Матрица n*n наборов (множеств) символов
    // Множество символов в [i][j] ячейке соответствует
    // множеству символов на ребре из i в j вершину
    // Напр.: a,b,varepsilon соответствует ребру a+b+\varepsilon
    std::vector<std::vector<std::set<char>>> edges_matrix;
    std::set<int> accepting_states;
    size_t states_count;
};

int main() {
    std::cout << varepsilon;
    CAutomata whatever('a');

    return 0;
}