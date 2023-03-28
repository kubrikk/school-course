#include <iostream>


using namespace std;


void quick_sort(int* arr, int size) {

    if (size < 2) {
        return;
    }

    int cur = arr[size / 2];

    int left = 0;
    int right = size - 1;
    while (left < right) {

        while (arr[left] < cur) {
            left++; 
        }
        while (arr[right] > cur) {
            right--;
        }
        if (left > right) {
            break;
        }

        swap(arr[left++], arr[right--]);

    }

    quick_sort(arr, right + 1);
    quick_sort(arr + left, size - left);

}


int main() {

    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quick_sort(arr, n);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;

    return 0;
}