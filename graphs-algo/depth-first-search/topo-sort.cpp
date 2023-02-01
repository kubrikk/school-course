#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool dfs(
        int vertex,
        vector< vector< int > >& graph,
        vector< int >& is_visited,
        vector< int >& ans
) {
    is_visited[vertex] = 1;

    bool result = 0;
    for (int i = 0; i < graph[vertex].size(); i++) {
        if (!is_visited[graph[vertex][i]]) {
            result += dfs(graph[vertex][i], graph, is_visited, ans);
        }
        else if (is_visited[graph[vertex][i]] == 1) {
            return 1;
        }
    }

    is_visited[vertex] = result == 1 ? 1 : 2;
    ans.push_back(vertex);
    
    return result;
}

bool is_cycle(
        vector< vector< int > >& graph,
        vector< int >& ans
) {

    vector< int > is_visited(graph.size(), 0);

    bool result = 0;
    for (int i = 1; i < graph.size(); i++) {
        if (!is_visited[i]) {
            result += dfs(i, graph, is_visited, ans);
        }
    }

    int ans_size = ans.size();
    for (int i = 0; i < ans_size / 2; i++) {
        int tmp = ans[i];
        ans[i] = ans[ans_size - i - 1];
        ans[ans_size - i - 1] = tmp;
    }

    return result;
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

    vector< int > result;
    if (!is_cycle(graph, result)) {
        cout << "Yes" << endl;
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << ' ';
        }
        cout << endl;
    }
    else {
        cout << "No" << endl;
    }

    return 0;
}