
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>

#include "../MatchTime.h"

using namespace std;

// void print_tm(Time tm) {
//     cout << setw(2) << setfill('0') << tm.hours << ":";
//     cout << setw(2) << setfill('0') << tm.mins << ":";
//     cout << setw(2) << setfill('0') << tm.secs << endl;
// }

int main(void) {
    Time tm;
    cout << tm << endl;

    tm += 60;
    cout << tm << endl;

    tm += 75;
    cout << tm << endl;

    tm += 86400/2;
    cout << tm << endl;

    tm += 86400/2;
    cout << tm << endl;

    tm += 19800;
    cout << tm << endl;

    cout << endl;

    MatchTime mt;
    cout << mt << endl;

    mt.delivery(false, 0);
    cout << mt << endl;


    return 0;
}
