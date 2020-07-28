
#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include <string>

#include "Player.h"
#include "Cards.h"

// Utility function for splitting string at passed delimeter
std::vector<std::string> split_str(std::string str, std::string delim = ",");

// Join individual strings into one
std::string join_str(std::vector<std::string> str_comp, std::string join = "");

Player* csv_to_player(std::string line);

Team load_team(std::string dir);
void save_team(Team team, std::string dir);



#endif