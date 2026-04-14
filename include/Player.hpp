#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Hand.hpp"
#include "BlackjackRules.hpp"

class Player {
public:
	std::vector<Hand> hands {};

	Player(std::string name);
	virtual ~Player();
	
	void clearHands();
	Hand& startNewHand(double bet);

	std::string getName() const;
	double getBankroll() const;

	virtual Action makeDecision(const Hand& currentHand, const Card& dealerUpCard, const BlackjackRules& rules) = 0;

	void win(double bet);
	void lose(double bet);

private:
	std::string name {};
	double bankroll {};
};

#endif // !PLAYER_H
