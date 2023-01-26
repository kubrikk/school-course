/*  COMPONENTS OF GRAPH (BFS) -------------------------------------------------

    В данном файле на основе классической реалицзации BFS описывается 
    решение задачи по выделению компонент связности неориентированного графа.

---------------------------------------------------------------------------  */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main() {

    // n -- количество вершин, m -- количество рёбер
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

    // ввод информации о m рёбрах
    for (int i = 0; i < m; i++) {
        int first_vertex, second_vertex;
        cin >> first_vertex >> second_vertex;
        // устанавливаем связь ребра (first_vertex, second_vertex)
        graph[first_vertex].push_back(second_vertex);
        graph[second_vertex].push_back(first_vertex);
    }

    int color = 1;  // метка для раскраски вершин одной компоненты
    // обнаружаем непомеченную вершину и выделяем компоненту связности,
    // сассоциированную с ней (с помощью BFS)
    for (int start_vetrex = 1; start_vetrex < n + 1; start_vetrex++) {

        // если вершина помечена -- компонента связности с этой вершиной
        // уже выделена
        if (is_visited[start_vetrex] != 0) {
            continue;
        }

        // иначе запускам BFS от этой вершины
        // реализацию BFS можно рассмотреть в отдельном файлике
        queue< int > bfs_queue;
        bfs_queue.push(start_vetrex);
        is_visited[start_vetrex] = color;

        while (!bfs_queue.empty()) {

            int this_vertex = bfs_queue.front();
            bfs_queue.pop();

            for (int i = 0; i < graph[this_vertex].size(); i++) {
                if (is_visited[graph[this_vertex][i]] == 0) {
                    bfs_queue.push(graph[this_vertex][i]);
                    // метим вершины номером компоненты связности
                    is_visited[graph[this_vertex][i]] = color;
                }
            }
        }

        color += 1;  // переходим к следующей компоненте
    }

    // выводим информацию о принадлежности вершин компонентам связности
    for (int i = 1; i < n + 1; i++) {
        cout << is_visited[i] << ' ';
    }
    cout << '\n';

    return 0;
}