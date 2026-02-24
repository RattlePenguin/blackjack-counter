#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Hand.hpp"

class Player {
public:
	Player(std::string name);
	
	void clearHands();
	void startNewHand(double bet);

	std::string getName() const;
	double getBankroll() const;

private:
	std::string name {};
	std::vector<Hand> hands {};
	double bankroll {};
};

#endif // !PLAYER_H
