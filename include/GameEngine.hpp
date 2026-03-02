#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "Shoe.hpp"
#include "BlackjackRules.hpp"
#include "Hand.hpp"
#include "Player.hpp"

class GameEngine {
public:
	GameEngine(int numDecks, int penetration);
private:
	Shoe shoe;
	BlackjackRules rules {};
	std::vector<Player*> players {};
	Hand* dealerHand;

	bool dealerShouldHit();
	void addPlayer(Player* player);
	void playRound();
	void startHands();
	void resolveRound();
};

#endif // !GAMEENGINE_H
