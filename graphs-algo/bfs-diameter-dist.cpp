/*  DIAMETER  -----------------------------------------------------------------



---------------------------------------------------------------------------  */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int furthest_vertex(
    int start_vertex, 
    vector< vector< int > >& graph,
    vector< int >& dist
) {
    
    queue< int > bfs_queue;
    bfs_queue.push(start_vertex);
    dist[start_vertex] = 0;

    while (!bfs_queue.empty()) {

        int this_vertex = bfs_queue.front();
        bfs_queue.pop();

        for (int i = 0; i < graph[this_vertex].size(); i++) {
            if (dist[graph[this_vertex][i]] == -1) {
                bfs_queue.push(graph[this_vertex][i]);
                dist[graph[this_vertex][i]] = dist[this_vertex] + 1;
            }
        }
    }

    int result_vertex = start_vertex;
    for (int vertex = 1; vertex < graph.size(); vertex++) {
        if (dist[result_vertex] < dist[vertex]) {
            result_vertex = vertex;
        }
    }

    return result_vertex;
}

int diameter(vector< vector< int > >& graph) {

    vector< int > dist(graph.size(), -1);
    int first_diameter_vertex = furthest_vertex(1, graph, dist);
    

    for (int i = 0; i < dist.size(); i++) {
        dist[i] = -1;
    }
    int second_diameter_vertex = 
        furthest_vertex(first_diameter_vertex, graph, dist);

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

    cout << diameter(graph) << '\n';

    return 0;
}