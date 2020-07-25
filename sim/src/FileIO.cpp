
#include <string>
#include <fstream>

#include "FileIO.h"
#include "Player.h"
#include "Utility.h"

using namespace std;

string* split_str(string str, string delim = ",") {
    size_t pos = 0;
    string* token;
    int i = 0;

    while ((pos = str.find(delim)) != string::npos) {
        token = arr_add_item<string>(token, i, str.substr(0, pos));
        str.erase(0, pos + delim.length());
        i++;

    return token;
}


Team load_file(string filename) {
    Team output;
    string line;
    int i = 0;

    // Open file and parse line-by-line
    ifstream f (filename);
    if (f.is_open()) {
        while (getline (f, line)) {
            if (i == 0) {
                Team.name = line;
            } else if (i == 12) {
                // Details on player roles
                string* nums = split_str(line, ',')
                Team.captain = nums[0];
                Team.wicket_keeper = nums[1];
                Team.bowl_open1 = nums[2];
                Team.bowl_open2 = nums[3];

            }

            // Otherwise, create a new player
            Team.players[i - 1] = new Player(line);

            i++;
        }
        
        f.close();
    }

    return output;

}