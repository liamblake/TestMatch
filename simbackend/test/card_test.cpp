#include <iostream>
#include <string>

#include "Player.h"
#include "Cards.h"
#include "Utility.h"

using namespace std;

int main(void) {
    // Create a batter
    Stats m_stats;
	m_stats.innings = 23;
	m_stats.bat_avg = 63.43;
	m_stats.bat_sr = 56.52;

	m_stats.balls_bowled = 756;
	m_stats.bowl_avg = 38.66;
	m_stats.bowl_sr = 63.0;
	m_stats.bowl_econ = 3.68;

	m_stats.bat_hand = false;
	m_stats.bowl_type = encode_bowltype("lb");

    Player p ("Marnus", "", "Labuschagne", "Australia", m_stats);
    

    Stats b_stats;
    b_stats.innings = 119;
	b_stats.bat_avg = 13.59;
	b_stats.bat_sr = 44.28;

	b_stats.balls_bowled = 18608;
	b_stats.bowl_avg = 22.95;
	b_stats.bowl_sr = 42.3;
	b_stats.bowl_econ = 3.24;

	b_stats.bat_hand = false;
	b_stats.bowl_type = encode_bowltype("rf");
    
    Player b ("Dale", "Willem", "Steyn", "South Africa", b_stats);


    BatterCard card(&p);
    BowlerCard bcard(&b);

    cout << card.print_card() << endl;

    // Face some "deliveries"
    for (int i = 0; i < 10; i++) {
        card.update_score("0");
        bcard.update_score("0");
    }
    cout << card.print_card() << endl;
    cout << bcard.print_card() << endl;

    card.update_score("4b");
    card.update_score("4");
    bcard.update_score("4b");
    bcard.update_score("4");
    cout << card.print_card() << endl;
    cout << bcard.print_card() << endl;

    card.update_score("0");
    card.update_score("1w");
    bcard.update_score("0");
    bcard.update_score("1w");
    cout << card.print_card() << endl;
    cout << bcard.print_card() << endl;

    // Dismiss
    card.update_score("W");
    bcard.update_score("W");
    card.dismiss(0, &b);
    cout << card.print_card() << endl;
    cout << bcard.print_card() << endl;

}

