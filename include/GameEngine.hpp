#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "Shoe.hpp"
#include "BlackjackRules.hpp"
#include "Hand.hpp"
#include "Player.hpp"

class GameEngine {
public:
	GameEngine(int numDecks, double penetration);
	~GameEngine();

	void addPlayer(Player* player);
	void playRound();
private:
	Shoe shoe;
	BlackjackRules rules {};
	std::vector<Player*> players {};
	Hand* dealerHand;

	bool dealerShouldHit();
	void startHands();
	void resolveRound();
};

#endif // !GAMEENGINE_H
