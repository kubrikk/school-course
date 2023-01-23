#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


void vertex_short_cycle(
        int start_vertex, 
        vector< vector< int > >& graph,
        vector< int >& parent,
        vector< int >& pre_result
) {

    queue< int > bfs_queue;
    bfs_queue.push(start_vertex);
    while (!bfs_queue.empty()) {
        
        int this_vertex = bfs_queue.front();
        bfs_queue.pop();

        for (int i = 0; i < graph[this_vertex].size(); i++) {
            if (parent[graph[this_vertex][i]] == -1) {
                parent[graph[this_vertex][i]] = this_vertex;
                bfs_queue.push(graph[this_vertex][i]);
            }
        }
    }

    if (parent[start_vertex] == -1) {
        return;
    }

    int next_vertex = start_vertex;
    do {
        pre_result.push_back(next_vertex);
        next_vertex = parent[next_vertex];
    } while (next_vertex != start_vertex);
    
    return;
}

void shortest_cycle(
        vector< vector< int > >& graph, 
        vector< int >& result
) {

    result.resize(graph.size(), -1);
    for (int vertex = 1; vertex < graph.size(); vertex++) {

        vector< int > parent(graph.size(), -1);
        vector< int > pre_result;
        
        vertex_short_cycle(vertex, graph, parent, pre_result);
        if (result.size() >= pre_result.size()) {
            result.clear();
            for (int i = 0; i < pre_result.size(); i++) {
                result.push_back(pre_result[i]);
            }
        }
    }
    reverse(result.begin(), result.end());

    return;
}

int main() {

    int n, m;
    cin >> n >> m;

    vector< vector< int > > graph(n + 1);
    for (int i = 0; i < m; i++) {
        int first_vertex, second_vertex;
        cin >> first_vertex >> second_vertex;
        graph[first_vertex].push_back(second_vertex);
    }

    vector< int > result_shortest_cycle;
    shortest_cycle(graph, result_shortest_cycle);

    cout << result_shortest_cycle.size() << endl;
    for (int i = 0; i < result_shortest_cycle.size(); i++) {
        cout << result_shortest_cycle[i] << ' ';
    }
    cout << endl;

    return 0;
}