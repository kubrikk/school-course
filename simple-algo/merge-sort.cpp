#include <iostream>

using namespace std;


void __merge(int* l_arr, int l_size, int* r_arr, int r_size, int* res) {

    int left = 0;
    int right = 0;
    int res_ind = 0;

    while (left < l_size && right < r_size) {
        if (l_arr[left] < r_arr[right]) {
            res[res_ind] = l_arr[left];
            left++;
        }
        else {
            res[res_ind] = r_arr[right];
            right++;
        }
        res_ind++;
    }

    while (left < l_size) {
        res[res_ind] = l_arr[left];
        left++;
        res_ind++;
    }
    while (right < r_size) {
        res[res_ind] = r_arr[right];
        right++;
        res_ind++;
    }

}


void merge_sort(int* arr, int size) {

    if (size < 2) {
        return;
    }

    int mid = size / 2;
    merge_sort(arr, mid);
    merge_sort(arr + mid, size - mid);

    int temp[size];
    __merge(arr, mid, arr + mid, size - mid, temp);

    for (int i = 0; i < size; i++) {
        arr[i] = temp[i];
    }

}


int main() {

    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    merge_sort(arr, n);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;

    return 0;

}