#include <string>
#include <fstream>
#include <utility>

#include "FileIO.h"
#include "Player.h"
#include "Utility.h"


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

         // Create Player object
         //Player* output = new Player ();
         //return output;
         return nullptr;

}






std::pair<Venue**, int>* load_venues(std::string dir) {
    std::pair<Venue**, int>* output = new std::pair<Venue**, int>* output;
}
