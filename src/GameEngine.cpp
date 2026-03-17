#include <iostream>

#include "GameEngine.hpp"

GameEngine::GameEngine(int numDecks, double penetration)
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
		std::cout << "[Dealer] Ace showing. Insurance? Y/N INCOMPLETE\n";
	}

	if (dealerHand->isBlackjack()) {
		std::cout << "[Dealer] shows Blackjack.\n";
		resolveRound();
		return;
	}

	// Clockwise, ask players for decisions and finish their game before moving to next player.
	for (auto* p : players) {
		// Iterate over all hands, dynamic sizing to allow splitting
		for (int i = 0; i < static_cast<int>(p->hands.size()); ++i) {
			Hand& currentHand { p->hands[static_cast<size_t>(i)] };
			while (!currentHand.isFinished()) {
				printTurn(currentHand);

				if (currentHand.isBusted()) {
					std::cout << "---> BUSTED\n";
					currentHand.finish();
					break;
				}

				if (currentHand.isBlackjack()) {
					std::cout << "---> BLACKJACK!\n";
					currentHand.finish();
					break;
				}

				if (currentHand.is21()) {
					std::cout << "---> 21\n";
					currentHand.finish();
					break;
				}

				Action action { p->makeDecision(currentHand, rules) };

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
						Card splitCard { currentHand.pop_back() };
						splitHand.addCard(splitCard);
						currentHand.split();
						splitHand.split();
						
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
						// TODO HANDLE BETS
						currentHand.finish();
						break;
				}
			}
		}
	}

	dealerTurn();
	resolveRound();
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

/**
 *  Hands have finished, handle payouts.
 *  Players modify their own bankrolls for profit/loss.
*/
void GameEngine::resolveRound() {
	bool dBlackjack { dealerHand->isBlackjack() };

	for (auto* p : players) {
		std::cout << p->getName() << " results\n";
		for (const Hand& h : p->hands) {
			std::cout << "Hand: ";
			h.printHand();

			if (h.isBusted()) {
				std::cout << "Lost " << h.getBet();
				p->lose(h.getBet());
				continue;
			}

			if (dealerHand->isBusted()) {
				std::cout << "Win " << h.getBet();
				p->win(h.getBet());
				continue;
			}
			
			// Natural blackjacks win
			if (dBlackjack && !h.isBlackjack()) {
				std::cout << "Lost " << h.getBet();
				p->lose(h.getBet());
				continue;
			} else if (!dBlackjack && h.isBlackjack()) {
				p->win(h.getBet());
				std::cout << "Won " << h.getBet();
				continue;
			}

			if (dealerHand->getRealValue() < h.getRealValue()) {
				p->win(h.getBet());
				std::cout << "Won " << h.getBet();
			} else if (dealerHand->getRealValue() > h.getRealValue()) {
				p->lose(h.getBet());
				std::cout << "Lost " << h.getBet();
			}
			// push
		}
	}
}
