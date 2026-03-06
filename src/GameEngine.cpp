#include <iostream>

#include "GameEngine.hpp"

GameEngine::GameEngine(int numDecks, int penetration)
	: shoe(numDecks, penetration)
	, dealerHand { nullptr }
{}

GameEngine::~GameEngine() {
	delete dealerHand;
}

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

	Card dealerUpCard = dealerHand->getCards().front(); // First card is the up card
	
	if (dealerUpCard.rank == Rank::ACE) {
		std::cout << "[Dealer] Ace showing. Insurance? Y/N\n";
	}

	if (dealerHand->isBlackjack()) {
		std::cout << "[Dealer] shows Blackjack.\n";
		resolveRound();
		return;
	}

	// Clockwise, ask players for decisions and finish their game before moving to next player.
	for (auto* p : players) {
		// Iterate over all hands, dynamic sizing to allow splitting
		for (int i = 0; i < p->hands.size(); ++i) {
			Hand& currentHand { p->hands[i] };
			while (!currentHand.isFinished()) {
				if (currentHand.isBusted()) {
					std::cout << "---> BUSTED\n";
					currentHand.finish();
					continue;
				}

				if (currentHand.is21()) {
					std::cout << "---> 21\n";
					currentHand.finish();
					continue;
				}

				Action action { p->makeDecision(currentHand, dealerUpCard, rules) };

				switch (action) {
					case Action::HIT:
						std::cout << "---> HIT\n";
						currentHand.addCard(shoe.draw());
						break;
					case Action::STAND:
						std::cout << "---> STAND\n";
						currentHand.finish();
						break;
					case Action::DOUBLE:
						std::cout << "---> DOUBLE DOWN\n";
						currentHand.doubleDown();
						currentHand.addCard(shoe.draw());
						currentHand.finish();
						break;
					case Action::SPLIT: {
						std::cout << "---> SPLIT\n";
						Hand splitHand { p->startNewHand(currentHand.getBet()) };
						Card splitCard { currentHand.split() };
						splitHand.addCard(splitCard);
						
						// Hit each hand
						currentHand.addCard(shoe.draw());
						splitHand.addCard(shoe.draw());
						
						// Split Aces get one card only.
						if (splitCard.rank == Rank::ACE) {
							currentHand.finish();
							splitHand.finish();
						}
						break;
					}
					case Action::SURRENDER:
						std::cout << "---> SURRENDER\n";
						currentHand.finish();
						break;
				}
			}
		}
	}

	// Dealer's turn
	std::cout << "\n[Dealer]'s Turn\n";
	dealerHand->getCards().back().faceDown = false;
	dealerHand->printHand();
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
