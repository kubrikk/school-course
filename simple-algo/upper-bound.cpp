#include <iostream>

using namespace std;


int upper_bound(int* arr, int size, int elem) {
    
    int left = 0;
    int right = size;

    while (right - left > 1) {
        int middle = (right + left) / 2;
        if (arr[middle] <= elem) {
            left = middle;
        }
        else {
            right = middle;
        }
    }

    return arr[left] == elem ? left : -1;
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

    cout << upper_bound(arr, n, elem) << endl;

    delete[] arr;

    return 0;
}