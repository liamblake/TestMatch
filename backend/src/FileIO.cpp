
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "FileIO.h"
#include "Player.h"
#include "Utility.h"

using namespace std;



Team load_team(string dir) {
    Team output;
    string line;
    int i = 0;

    // Open file and parse line-by-line
    ifstream file (dir);
    if (file.is_open()) {

        while (getline(file, line)) {
            if (i == 0) {
                output.name = line;

            } else if (i == 12) {
                // Details on player roles
                vector<string> nums = split_str(line);
                output.captain = stoi(nums[0]) - 1;
                output.wicket_keeper = stoi(nums[1]) - 1;
                output.bowl_open1 = stoi(nums[2]) - 1;
                output.bowl_open2 = stoi(nums[3]) - 1;

            } else {

                // Otherwise, create a new player
                output.players[i - 1] = new Player(line);
            }
            
            i++;
        
        }
        
        file.close();
    } else {
        cout << "Failed to open file at " << dir << endl;
    }

    return output;

}


void save_team(Team team, string dir) {


    // Open file for writing
    ofstream file (dir);


    file.close();


}