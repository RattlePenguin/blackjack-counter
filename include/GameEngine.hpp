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
	
	/**
	 *  Adds a player to the game.
	 */
	void addPlayer(Player* player);

	/**
	 *  Starts a game of Blackjack.
	 */
	void playRound();

private:
	Shoe shoe;
	BlackjackRules rules {};
	std::vector<Player*> players {};
	Hand* dealerHand;

	bool dealerShouldHit();
	void startHands();
	void dealerPreCheck();
	void resolveRound();
	void printTurn(Hand& hand);
	void dealerTurn();
	void clearHands();
};

#endif // !GAMEENGINE_H
