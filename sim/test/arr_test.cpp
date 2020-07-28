
#include <iostream>
#include <string>

#include "Utility.h"

using namespace std;

template <typename T>
void print_arr(T* arr, int length) {
    for (int i = 0; i < length; i++) {        
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(void) {
    // Empty array
    int* empt;
    empt = arr_add_item<int>(empt, 0, 1);
    print_arr<int>(empt, 1);
    
    // Standard integer array
    int* arr = new int[3];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    print_arr<int>(arr, 3);

    arr = arr_add_item<int>(arr, 3, 5);
    print_arr<int>(arr, 4);


    // String array
    string* str = new string[2];
    str[0] = "a";
    str[1] = "b";
    print_arr<string>(str, 2);

    str = arr_add_item<string>(str, 2, "c");
    print_arr<string>(str, 3);


    delete[] arr, str;
}
