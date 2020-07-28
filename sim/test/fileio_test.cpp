
#include <iostream>
#include <string>
#include <vector>

#include "FileIO.h"
#include "Player.h"

using namespace std;

int main(void) {
    // Test split string function
    // cout << "Testing split_str..." << endl;
    // vector<string> arr = split_str("a,b,c,d,e");
    // for (int i = 0; i < 5; i++) {
    //     cout << arr[i] << endl;
    // }


    cout << "Loading team..." << endl;
    Team x = load_team("D:\\Dropbox\\Projects\\TestMatch\\sim\\test\\teams\\newzealand.dat");
    cout << "Load finished." << endl;
    cout << x;

    return 0;
}