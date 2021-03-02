#include <string>
#include <fstream>

#include "FileIO.h"
#include "Player.h"
#include "Utility.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

template <class T>
void save_data(T* obj, std::string filename) {
    // Open character archive for output
    std::ofstream ofs(filename);

    // Save data 
    {
        boost::archive::text_oarchive oa(ofs);
        oa << *obj;
    }
}

template <class T>
T* load_data(std::string filename) {
    // New object
    T* newobj; 
    {
        // Create and open an archive for input
        std::ifstream ifs(filename)
        boost::archive::text_iarchive ia(ifs);

        ia >> *newobj;
    }

    return newobj;
}




// Player* csv2player(std::string line) {
//         // Split string
//         std::vector<std::string> token = split_str(line);

//         vector<string> name = split_str(token[1], " ");
//         std::string inits = name[0];

//         // Find first name in fullname with matching initial
//         char finit = inits[0];

//         // Check first character
//         std::string fname;
//         std::string fullname = token[0];
//         std::vector<std::string> full_split = split_str(fullname, " ");

//         if (fullname[0] == finit) {
//             fname = full_split[0];
//         }
//         else {
//             // Need to search string components
//             vector<string>::iterator it = full_split.begin();
//             while (it != full_split.end() && (*it)[0] != finit) {
//                 it++;
//             }

//             if (it <= full_split.end()) {
//                 fname = *it;
//             }


//         }

//         name.erase(name.begin());
//         string last_name = join_str(name, " ");

//         // Create Player object
//         //Player* output = new Player ();
//         //return output;
//         return nullptr;

// }


// Team* load_team(string dir) {
//     Team* output = new Team;
//     string line;
//     int i = 0;

//     // Open file and parse line-by-line
//     ifstream file (dir);
//     if (file.is_open()) {

//         while (getline(file, line)) {
//             if (i == 0) {
//                 output->name = line;

//             } else if (i == 12) {
//                 // Details on player roles
//                 vector<string> nums = split_str(line);
//                 output->i_captain = stoi(nums[0]) - 1;
//                 output->i_wk = stoi(nums[1]) - 1;
//                 output->i_bowl1 = stoi(nums[2]) - 1;
//                 output->i_bowl2 = stoi(nums[3]) - 1;

//             } else {

//                 // Otherwise, create a new player
//                 output->players[i - 1] = csv2player(line);
//             }
            
//             i++;
        
//         }
        
//         file.close();
//     } else {
//         cout << "Failed to open file at " << dir << endl;
//     }

//     return output;

// }


// void save_team(Team team, string dir) {


//     // Open file for writing
//     ofstream file (dir);


//     file.close();


// }