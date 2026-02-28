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
	if (shoe.needsShuffle()) {
		std::cout << "[Dealer] Shuffling the shoe...\n";
		shoe.shuffle();
	}
	// Deal cards
	// Ask player 1 for decision
	// ... Clockwise order
	//
	//
	// 2. Bets & Initial Deal
        dealerHand = new Hand(0); // Dealer has no bet
        
        // Deal 2 cards to everyone
        // Standard procedure: Card 1 to players, Card 1 to dealer, Card 2 to players, Card 2 to dealer.
        for (int i = 0; i < 2; ++i) {
            for (auto* p : players) {
                if (i == 0) {
                     // In a real app, ask for bet amount here.
                     // For now, fixed bet of 10.
                     p->startNewHand(10.0); 
                }
                // Deal to the LAST hand of the player (since they only have 1 right now)
                p->hands.back().addCard(shoe.deal());
            }
            dealerHand->addCard(shoe.deal());
        }
}
