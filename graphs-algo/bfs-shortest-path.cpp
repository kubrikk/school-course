/*  SHORTEST PATH  ------------------------------------------------------------



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
    // 
    vector< int > parent(n + 1, -1);

    // ввод информации о `m` рёбрах
    for (int i = 0; i < m; i++) {
        int first_vertex, second_vertex;
        cin >> first_vertex >> second_vertex;
        // устанавливаем связь ребра (`first_vertex`, `second_vertex`)
        graph[first_vertex].push_back(second_vertex);
        graph[second_vertex].push_back(first_vertex);
    }

    // 
    int start_vertex, finish_vertex;
    cin >> start_vertex >> finish_vertex;

    // создаём очередь для последующей реализации BFS
    queue< int > bfs_queue;
    bfs_queue.push(start_vertex);  // 
    parent[start_vertex] = start_vertex;  // 

    while (!bfs_queue.empty()) {

        // достаём из очереди очередную вершину
        int this_vertex = bfs_queue.front();
        bfs_queue.pop();

        // и рассматриваем её соседей
        for (int i = 0; i < graph[this_vertex].size(); i++) {
            // 
            if (parent[graph[this_vertex][i]] == -1) {
                // 
                bfs_queue.push(graph[this_vertex][i]);
                // 
                parent[graph[this_vertex][i]] = this_vertex;
            }
        }
    }

    vector< int > path;
    int temp_vertex = finish_vertex;
    while (parent[temp_vertex] != temp_vertex) {
        path.push_back(temp_vertex);
        temp_vertex = parent[temp_vertex];
    }
    path.push_back(temp_vertex);

    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i] << ' ';
    }
    cout << '\n';
    
    return 0;
}