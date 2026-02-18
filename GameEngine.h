#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "Shoe.h"
#include "BlackjackRules.h"
#include "Hand.h"
#include "Player.h"

class GameEngine {
public:
	GameEngine(int numDecks, int penetration);
private:
	Shoe shoe;
	BlackjackRules rules {};
	std::vector<Player*> players {};
	Hand* dealerHand;

	bool dealerShouldHit();
	void addPlayer(Player& player);
	void playRound();
	void resolveRound();
};

#endif // !GAMEENGINE_H
