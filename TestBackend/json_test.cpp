#include "pch.h"
#include <string>
#include <iostream>
#include "ThorSerialize/Traits.h"
#include "ThorSerialize/JsonThor.h"


// Player as collection of strings
struct StringPlayer {
	std::string first_name;
	std::string middle_name;
	std::string last_name;

	//std::string innings;
	//std::string bat_avg;
	//std::string bat_sr;

	//std::string balls_bowled;
	//std::string bowl_avg;
	//std::string bowl_sr;
	//std::string bowl_econ;

	//std::string bat_hand;
	//std::string bowl_type;

};


struct StringTeam {
	std::string name;

	//InputPlayer team [11];

	std::string captain;
	std::string wk;
	std::string open_bowl1;
	std::string open_bowl2;
};


std::string team_to_json(StringTeam c_team) {
	return "yes";
}



int main(void) {
	StringTeam test;
	test.name = "TestTeam";
	test.captain = "1";
	test.wk = "7";
	test.open_bowl1 = "9";
	test.open_bowl2 = "11";

	std::cout << team_to_json(test);

	return 0;
}