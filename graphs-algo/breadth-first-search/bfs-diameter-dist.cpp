/*  DIAMETER DISTANCE ---------------------------------------------------------

    В данном файле описывается реализуется решения задачи нахождения диаметра 
    неориентрованного невзвешенного графа с использованием BFS

---------------------------------------------------------------------------  */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


// функция для нахождения самой удалённой вершины от заданной `start_vertex`
// в графе `graph` с сохранением расстояний до каждой вершины во внешнем 
// массиве `dist` 
int furthest_vertex(
        int start_vertex,                   // начальная вершина
        vector< vector< int > >& graph,     // ссылка на список смежности
        vector< int >& dist                 // ссылка на массив расстояний
                                            // (он заполнен `-1`-ми)
) {
    
    // классическая реализация BFS
    queue< int > bfs_queue;
    bfs_queue.push(start_vertex);
    dist[start_vertex] = 0;

    while (!bfs_queue.empty()) {

        int this_vertex = bfs_queue.front();
        bfs_queue.pop();

        for (int i = 0; i < graph[this_vertex].size(); i++) {
            if (dist[graph[this_vertex][i]] == -1) {
                bfs_queue.push(graph[this_vertex][i]);
                // храним кратчайшее расстояние до каждой вершины
                dist[graph[this_vertex][i]] = dist[this_vertex] + 1;
            }
        }
    }

    // находим самую удалённую от `start_vertex` вершину
    int result_vertex = start_vertex;
    for (int vertex = 1; vertex < graph.size(); vertex++) {
        if (dist[result_vertex] < dist[vertex]) {
            result_vertex = vertex;
        }
    }

    // возвращаем самую удалённую от `start_vertex` вершину
    return result_vertex;
}


// функция для нахождения длины диаметра (решение самой задачи)
int diameter(vector< vector< int > >& graph) {

    // создаём массив для хранения расстояний
    vector< int > dist(graph.size(), -1);
    // находим первую точку, определяющую диаметр, как саму удалённую
    // от произвольной точки
    int first_diameter_vertex = furthest_vertex(1, graph, dist);
    
    // обнуляем массив для хранения расстояний (для каждой точки не рассчитано)
    for (int i = 0; i < dist.size(); i++) {
        dist[i] = -1;
    }
    // запускаем функцию `furthest_vertex` от найденной вершины 
    // `first_diameter_vertex`, результат которой будет определять вторую 
    // вершину диаметра графа
    int second_diameter_vertex = 
        furthest_vertex(first_diameter_vertex, graph, dist);

    // возвращаем ответ на задачу
    return dist[second_diameter_vertex];
}


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

    // ввод информации о `m` рёбрах
    for (int i = 0; i < m; i++) {
        int first_vertex, second_vertex;
        cin >> first_vertex >> second_vertex;
        // устанавливаем связь ребра (`first_vertex`, `second_vertex`)
        graph[first_vertex].push_back(second_vertex);
        graph[second_vertex].push_back(first_vertex);
    }

    // вывод результата выполнения функции нахождения диаметра
    cout << diameter(graph) << '\n';

    return 0;
}