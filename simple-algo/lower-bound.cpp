#include <iostream>

using namespace std;


int lower_bound(int* arr, int size, int elem) {
    
    int left  = -1;
    int right = size - 1;

    while (right - left > 1) {
        int middle = (right + left) / 2;
        if (arr[middle] < elem) { left = middle; }
        else { right = middle; }
    }

    return arr[right] == elem ? right : -1;
}


int main() {

    int* arr;

    int n;
    cin >> n;

    arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int elem;
    cin >> elem;

    cout << lower_bound(arr, n, elem) << endl;

    delete[] arr;

    return 0;
}