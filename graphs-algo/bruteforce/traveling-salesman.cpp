#include <iostream>
#include <vector>


using namespace std;


bool next_permutation(vector<int>& seq) {

    int index = seq.size();
    for (int i = seq.size() - 1; i > 0; i--) {
        if (seq[i] > seq[i - 1]) {
            index = i;
            break;
        }
    }

    if (index == seq.size()) {
        return 0;
    }

    for (int i = seq.size() - 1; i > index - 1; i--) {
        if (seq[i] > seq[index - 1]) {
            swap(seq[i], seq[index - 1]);
            break;
        }
    }

    int dist = seq.size() - index;
    int seq_size = seq.size();
    for (int i = 0; i < dist / 2; i++) {
        swap(seq[index + i], seq[seq_size - 1 - i]);
    }

    return 1;
}


int main() {

    int n, m;
    cin >> n >> m;

    vector< vector< int > > matrix(n + 1);
    for (int i = 0; i < n + 1; i++) {
        matrix[i].resize(n + 1, 0);
    }

    for (int i = 0; i < m; i++) {
        int first, second, weight;
        cin >> first >> second >> weight;
        matrix[first][second] = weight;
        matrix[second][first] = weight;
    }

    vector< int > vertex_seq(n);
    for (int i = 0; i < n; i++) {
        vertex_seq[i] = i + 1;
    }

    int result = 1'000'000'000;
    do {
        
        bool correct_cycle = 1;
        int weight_sum = 0;
        for (int i = 0; i < n; i++) {
            correct_cycle *= matrix[vertex_seq[i]][vertex_seq[(i + 1) % n]];
            weight_sum += matrix[vertex_seq[i]][vertex_seq[(i + 1) % n]];
        }

        if (correct_cycle) {
            result = min(result, weight_sum);
        }

    } while (next_permutation(vertex_seq));

    cout << result << endl;

    return 0;
}