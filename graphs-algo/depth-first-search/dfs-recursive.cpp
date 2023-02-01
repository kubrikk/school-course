#include <iostream>
#include <vector>

using namespace std;


void dfs(
        int vertex,
        vector< vector< int > >& graph,
        vector< int >& is_visited
) {

    is_visited[vertex] = 1;
    for (int i = 0; i < graph[vertex].size(); i++) {
        if (!is_visited[graph[vertex][i]]) {
            dfs(graph[vertex][i], graph, is_visited);
        }
    }
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


    dfs(start_vertex, graph, is_visited);
    // выведим информацию о вершинах, входящих и не входящих в одну компоненту
    // связности с вершиной `start_vertex`
    for (int i = 1; i < n + 1; i++) {
        cout << is_visited[i] << ' ';
    }
    cout << '\n';

    return 0;
}