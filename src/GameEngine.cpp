#include <iostream>

#include "GameEngine.hpp"

GameEngine::GameEngine(int numDecks, int penetration)
	: shoe(numDecks, penetration)
	, dealerHand { nullptr }
{}

bool GameEngine::dealerShouldHit() {
	if (dealerHand->getRealValue() >= 17) {
		if (rules.hitSoft17 && dealerHand->isSoft()) {
			return true;
		}
		return false;
	}
	return true;
}

void GameEngine::addPlayer(Player* p) {
	players.push_back(p);
}

void GameEngine::playRound() {
	// To play a round, you need to
	// Check deck penetration, reshuffle if necessary
	if (shoe.needsShuffle()) {
		std::cout << "[Dealer] Shuffling the shoe...\n";
		shoe.shuffle();
	}
	// Deal cards
	// Ask player 1 for decision
	// ... Clockwise order
	//
}
