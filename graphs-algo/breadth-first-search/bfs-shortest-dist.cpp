/*  SHORTEST DISTANCE  --------------------------------------------------------

    В данном файле на основе BFS решается классическая задача нахождения 
    кратчайшего расстояния между двумя вершинами в неориентированном
    невзвешенном графе.

---------------------------------------------------------------------------  */

#include <iostream>
#include <vector>
#include <queue>

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
    // массив для хранения расстояний
    vector< int > dist(n + 1, -1);

    // ввод информации о `m` рёбрах
    for (int i = 0; i < m; i++) {
        int first_vertex, second_vertex;
        cin >> first_vertex >> second_vertex;
        // устанавливаем связь ребра (`first_vertex`, `second_vertex`)
        graph[first_vertex].push_back(second_vertex);
        graph[second_vertex].push_back(first_vertex);
    }

    // ввод вершин, расстояние между которыми необходимо найти
    int start_vetrex, finish_vertex;
    cin >> start_vetrex >> finish_vertex;

    // создаём очередь для последующей реализации BFS
    queue< int > bfs_queue;
    bfs_queue.push(start_vetrex);   // добавление в очередь первой вершины;
                                    // от данной вершины будет производиться 
                                    // поиск расстояний до всех остальных
    dist[start_vetrex] = 0;         // считаем, что расстояние `start_vertex`
                                    // до самой себя равен нулю

    while (!bfs_queue.empty()) {

        // достаём из очереди очередную вершину
        int this_vertex = bfs_queue.front();
        bfs_queue.pop();

        // и рассматриваем её соседей
        for (int i = 0; i < graph[this_vertex].size(); i++) {
            // если до соседа не было найдено расстояние
            if (dist[graph[this_vertex][i]] == -1) {
                // то добавляем его в очередь
                bfs_queue.push(graph[this_vertex][i]);
                // и считаем расстояние в форме расстояния до его предка 
                // (предка в дереве обхода) плюс 1
                dist[graph[this_vertex][i]] = dist[this_vertex] + 1;
            }
        }
    }

    // выводим полученное расстояние
    cout << dist[finish_vertex] << '\n';

    return 0;
}