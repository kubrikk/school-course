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

    int n;
    cin >> n;

    vector< int > seq(n);
    for (int i = 0; i < n; i++) {
        seq[i] = i + 1;
    }

    do {
        for (int i = 0; i < n; i++) {
            cout << seq[i] << ' ';
        }
        cout << endl;
    } while(next_permutation(seq));

    return 0;
}