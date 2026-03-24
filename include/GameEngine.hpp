#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "Shoe.hpp"
#include "BlackjackRules.hpp"
#include "Hand.hpp"
#include "Player.hpp"

class GameEngine {
public:
	GameEngine(int numDecks, double penetration, unsigned int seed);
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

	/**
	 *  Returns true if the dealer should hit based on rules, else false.
	 */
	bool dealerShouldHit();
	
	/**
	 *  Initialises hands for each player and the dealer as per Blackjack rules.
	 *  Creates a new Hand pointer for dealerHand.
	 */
	void startHands();

	/**
	 *  Prints all hands currently in play.
	 */
	void printHands();

	/**
	 *  Asks insurance on Ace up, natural blackjack peeks and handles late surrender.
	 *  Returns true if dealer has blackjack and game should end, else false.
	 */
	bool dealerPreCheck();


	/**
	 *  Plays out the given hand.
	 */
	void doTurn(Player* p, Hand& currentHand);

	/**
	 *  Resolves round after all hands have been played.
	 *  Handles payout.
	 */
	void resolveRound();

	/**
	 *  Prints the cards of the dealer hand and the current hand being played.
	 */
	void printTurn(Hand& hand);

	/**
	 *  Performs the dealer's turn.
	 *  Called after every player's hand is finished.
	 */
	void dealerTurn();

	/**
	 *  Clears hands for each player and the dealer.
	 *  Postcondition:
	 *		dealerHand == nullptr
	 */
	void clearHands();
};

#endif // !GAMEENGINE_H
