
#ifndef FILEIO_H
#define FILEIO_H

#include <string>

#include "Player.h"
#include "Cards.h"

// Utility function for splitting string at passed delimeter
std::string* split_str(std::string str, std::string delim);

Team load_file(std::string filename);
void save_team(Team team);




#endif