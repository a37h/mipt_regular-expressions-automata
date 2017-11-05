//
// Created by qua on 05.11.17.
//

#include "cautomata.h"

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

void CAutomata::PrintAutomata() {
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

std::vector<std::pair<size_t,char>> CAutomata::GetNextVerts(int verticeFrom) {
    std::vector<std::pair<size_t,char>> result;
    for (int i = 0; i < states_count; ++i) {
        if (edges_matrix[verticeFrom][i] != (char) 0) {
            std::pair<size_t,char> temp(i,edges_matrix[verticeFrom][i]);
            result.push_back(temp);
        }
    }
    return result;
}

size_t CAutomata::GetSize(){
    return states_count;
}