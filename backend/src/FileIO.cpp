
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "FileIO.h"
#include "Player.h"
//#include "Utility.h"

using namespace std;

vector<string> split_str(string str, string delim) {
    /* TODO: implement with string* return type to save memory,
             ideally using the arr_add_item template defined in
             Utility.h. Attempts at this have been giving strange
             results, where the while loop won't iterate unless 
             cout << len << endl is included at the start of the 
             loop.
    */

    vector<string> token;

    size_t curr, prev = 0;
    curr = str.find(delim);
    while (curr != string::npos) {
        token.push_back(str.substr(prev, curr - prev));
        prev = curr + 1;
        curr = str.find(delim, prev);

    }

    // Old, broken implementation
    // while ((pos = str.find(delim)) != string::npos) {
    //     cout << i << endl;
    //     token = arr_add_item<string>(token, i, str.substr(0, pos));
    //     str.erase(0, pos + delim.length());
    //     i++;
        
    //}

    // Add remaining string
    token.push_back(str.substr(prev, curr - prev));

    return token;
}

string join_str(vector<string> str_comp, string join) {
    string output = "";
    for (string x: str_comp) {
        output += x + join;
    }

    // Remove last join added in above loop
    return output.substr(0, output.size() - join.size());
}


Player* csv_to_player(string line) {
    // Split string
    vector<string> token = split_str(line);
    
    
    vector<string> name = split_str(token[1], " ");
    string inits = name[0];

    // Find first name in fullname with matching initial
    char finit = inits[0];
    
    // Check first character
    string fname;
    string fullname = token[0];
    vector<string> full_split = split_str(fullname, " ");

    if (fullname[0] == finit) {
        fname = full_split[0];
    } else {
        // Need to search string components
        vector<string>::iterator it = full_split.begin();
        while (it != full_split.end() && (*it)[0] != finit) {
            it++;
        }

        if (it <= full_split.end()) {
            fname = *it;
        }


    }

    /* This clearly won't work if the name used by the player isn't
       that given by the first initial or the first name with that
       initial.
    e.g. MJ Leach goes by Jack Leach, but this implementation will 
         store him as Matthew Leach

       TODO: develop a better solution to this problem
    */

    // Player stats
    Stats stats;


    name.erase(name.begin());
    string lname = join_str(name, " ");

    Player* player = new Player(fname, lname, inits, stats, token[2]);
    return player;
}


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
                output.players[i - 1] = csv_to_player(line);
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