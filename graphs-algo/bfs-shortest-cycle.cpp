/*  SHORTEST CYCLE ------------------------------------------------------------

    В данном файле описывается реализация решения задачи нахождения кратчайшего
    цикла в ориентированном невзвешенном графе. В реализации используется BFS

---------------------------------------------------------------------------  */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


// функция для нахождения кратчайшего цикла, в который входит 
// вершина `start_vertex`
void vertex_short_cycle(
        int start_vertex,               // вершина, которая содержится в цикле
        vector< vector< int > >& graph, // ссылка на граф (список смежности)
        vector< int >& parent,          // ссылка на массив для хранения  
                                        //      предков в порядке обхода
        vector< int >& pre_result       // ссылка на массив с минимальным циком 
                                        //       -- результат 
) {

    // запускаем BFS от вершины `start_vertex`, но при этом не метим её при
    // первом добавлении в очередь
    queue< int > bfs_queue;
    bfs_queue.push(start_vertex);
    while (!bfs_queue.empty()) {
        
        int this_vertex = bfs_queue.front();
        bfs_queue.pop();

        for (int i = 0; i < graph[this_vertex].size(); i++) {
            if (parent[graph[this_vertex][i]] == -1) {
                // для каждой вершины запоминаем его предка в порядке обхода
                parent[graph[this_vertex][i]] = this_vertex;
                bfs_queue.push(graph[this_vertex][i]);
            }
        }
    }

    // если в результате обхода вершина второй раз не попала в очередь, значит
    // цикла с данной вершиной не существует
    if (parent[start_vertex] == -1) {
        return;     // заканчиваем выполнение функции от данной вершины
    }


    // иначе восстанавливаем путь, запоминая его в массиве `pre_result`
    int next_vertex = start_vertex;
    do {
        pre_result.push_back(next_vertex);
        next_vertex = parent[next_vertex];
    } while (next_vertex != start_vertex);
    
    return;
}


// функция для находждения минимального цикла в графе, которая принимает
void shortest_cycle(
        vector< vector< int > >& graph, // ссылка на граф (список смежности) 
        vector< int >& result           // ссылка на массив с описанием 
                                        //      минимального цикла в графе 
                                        //      -- результат
) {

    // делаем невозможно большой массив, в качестве гипотезы отсутсвия цикла
    result.resize(graph.size(), -1);
    // пройдймся по всем вершинам с целью опровергнуть гипотезу
    for (int vertex = 1; vertex < graph.size(); vertex++) {
        
        // массив для хранения предков в порядке обхода в ширину
        vector< int > parent(graph.size(), -1);
        // массив для предполагаемого опровержения локального минимума
        vector< int > pre_result;
        
        // пробуем найти минимальный цикл с вершиной `vertex`
        vertex_short_cycle(vertex, graph, parent, pre_result);
        // если цикла нет, переходим к следующей вершине
        if (pre_result.size() == 0) {
            continue;
        }

        // иначе проверяем, найденный цикл может быть короче рассмотренных
        //                                                   ранее
        if (result.size() >= pre_result.size()) {
            result.clear();     // тогда перезаписываем массив `result`
            for (int i = 0; i < pre_result.size(); i++) {
                result.push_back(pre_result[i]);
            }
        }
    }

    // если цикла не было найдено, делаем вектор ответа пустым
    if (result.size() == graph.size()) {
        result.clear();
    }

    // иначе переворачиваем (изначально цикл записан в обратном порядке)
    reverse(result.begin(), result.end());

    return;
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
        // устанавливаем связь ориентированного ребра 
        // (`first_vertex`, `second_vertex`)
        graph[first_vertex].push_back(second_vertex);
    }

    // создаём массив для хранения результата
    vector< int > result_shortest_cycle;
    // решаем задачу
    shortest_cycle(graph, result_shortest_cycle);

    // выводим результат
    cout << result_shortest_cycle.size() << endl;
    for (int i = 0; i < result_shortest_cycle.size(); i++) {
        cout << result_shortest_cycle[i] << ' ';
    }
    cout << endl;

    return 0;
}