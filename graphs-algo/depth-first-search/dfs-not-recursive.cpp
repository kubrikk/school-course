/*  BFS  ----------------------------------------------------------------------

    В данном файле описывается классический алгоритм обхода графа (неориент.)
    -- поиск в глубину, обход в глубину, depth-first search (DFS)
    
    Приведена классическая нерекурсивная реализация DFS с использованием 
    стека для графа, представленного в форме списка смежности.
    Для реализации списка смежности используется vector, в качестве стека
    из стандартной библиотеки взят stack.

---------------------------------------------------------------------------  */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;


int main() {

    // `n` -- количество вершин, `m` -- количество рёбер
    int n, m;
    cin >> n >> m;

    /*
        ПРИМ. память под хранение информации о вершинах выделяется как `n + 1`
        с целью возможности обращения к вершинам по их имени (первые n 
        натуральных чисел)
    */ 

    // создаём вектор векторов для хранения списка смежности
    vector< vector< int > > graph(n + 1);
    // и массив меток для всех вершин
    vector< int > is_visited(n + 1, 0);

    // ввод информации о `m` рёбрах
    for (int i = 0; i < m; i++) {
        int first_vertex, second_vertex;
        cin >> first_vertex >> second_vertex;
        // устанавливаем связь ребра (`first_vertex`, `second_vertex`)
        graph[first_vertex].push_back(second_vertex);
        graph[second_vertex].push_back(first_vertex);
    }

    // выбираем стартовую вершину
    int start_vetrex;
    cin >> start_vetrex;

    // создаём стек для последующей реализации DFS
    queue< int > dfs_stack;
    dfs_stack.push(start_vetrex);  // добавляем стартовую вершину в стек
    is_visited[start_vetrex] = 1;  // отмечаем стартовую вершину

    while (!dfs_stack.empty()) {

        // достаём из очереди очередную вершину
        int this_vertex = bfs_queue.front();
        dfs_stack.pop();

        // и рассматриваем её соседей
        for (int i = 0; i < graph[this_vertex].size(); i++) {
            // если существует непомеченный сосед
            if (is_visited[graph[this_vertex][i]] == 0) {
                // добавляем его в стек
                dfs_stack.push(graph[this_vertex][i]);
                // делаем его помеченным
                is_visited[graph[this_vertex][i]] = 1;
            }
        }
    }

    // выведим информацию о вершинах, входящих и не входящих в одну компоненту
    // связности с вершиной `start_vertex`
    for (int i = 1; i < n + 1; i++) {
        cout << is_visited[i] << ' ';
    }
    cout << '\n';

    return 0;
}