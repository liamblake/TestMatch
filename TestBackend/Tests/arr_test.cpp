
#include <iostream>
#include "Encoders.h"

using namespace std;

void print_arr(int* arr, int length) {
    for (int i = 0; i < length; i++) {        
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(void) {
    int *arr = new int[3];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    print_arr(arr, 3);

    arr = arr_add_item<int>(arr, 3, 5);
    print_arr(arr, 4);
}
