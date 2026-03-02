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
	// Check and shuffle shoe.
	if (shoe.needsShuffle()) {
		std::cout << "[Dealer] Shuffling the shoe...\n";
		shoe.shuffle();
	}

	startHands();

	Card dealerUpCard = dealerHand->getCards()[0]; // First card is the up card
	
	if (dealerUpCard.rank == Rank::ACE) {
		std::cout << "[Dealer] Ace showing. Insurance? Y/N\n";
	}
	// Clockwise, ask players for decisions and finish their game before moving to next player.
}

/**
 *  Deals hands for all players and the dealer.
 *  Creates a new Hand pointer for dealerHand.
 */
void GameEngine::startHands() {
	dealerHand = new Hand(0); // Dealer has no bet
	
	// Deal 1 card to players then dealer, then repeat. Dealer up then downcard.
	for (int i = 0; i < 2; ++i) {
		for (auto* p : players) {
			if (i == 0) {
				 // In a real app, ask for bet amount here.
				 // For now, fixed bet of 10.
				 p->startNewHand(10.0); 
			}
			// Deal to the LAST hand of the player (since they only have 1 right now)
			p->hands.back().addCard(shoe.draw());
		}

		if (i == 0) {
			dealerHand->addCard(shoe.draw());
		} else {
			Card downCard = shoe.draw();
			downCard.faceDown = true;
			dealerHand->addCard(downCard);
		}
	}

}
