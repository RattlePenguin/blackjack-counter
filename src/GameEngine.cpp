#include <iostream>
#include <sstream>

#include "GameEngine.hpp"

double parseBet(Player* p);

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
	// Shuffle shoe if necessary.
	if (shoe.needsShuffle()) {
		std::cout << "[Dealer] Shuffling the shoe...\n";
		shoe.shuffle();
	}

	startHands();
	dealerPreCheck();
	Card dealerUpCard = dealerHand->getCards().front(); // First card is the up card

	for (auto* p : players) {
		// Dynamic sizing to allow splitting
		for (int i = 0; i < static_cast<int>(p->hands.size()); ++i) {
			Hand& currentHand { p->hands[static_cast<size_t>(i)] };
			doTurn(p, currentHand);
		}
	}

	dealerTurn();
	resolveRound();
}

void GameEngine::startHands() {
	dealerHand = new Hand(0); // Dealer has no bet
	
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < static_cast<int>(players.size()); ++j) {
			Player* p = players[j];

			if (i == 0) {
				if (j == 0) {
					p->startNewHand(parseBet(p));
				} else {
					p->startNewHand(10.0);
				}
			}
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
 *  Parses a string input into a double and returns it.
 */
double parseBet(Player* p) {
	double bet { -1 };
    std::string input;
    bool valid = false;
    while (!valid) {
		std::cout << "Enter your bet: ";
        std::getline(std::cin, input);

        std::stringstream ss(input);
        if (ss >> bet) {
            // Check if there are any non-whitespace characters left in the stringstream
            // (e.g., if the user entered "123abc")
            char remaining;
            if (ss >> remaining) {
                std::cout << "Invalid input." << std::endl;
            } else {
                valid = true;
            }
        } else {
            std::cout << "Invalid input." << std::endl;
        }
    }
	return bet;
}

void GameEngine::dealerPreCheck() {
	if (dealerHand->getCards().front().rank == Rank::ACE) {
		std::cout << "[Dealer] Ace showing. Insurance? Y/N: ";
	}
	
	// Peek
	if (rules.lateSurrender && dealerHand->isBlackjack()) {
		std::cout << "[Dealer] shows Blackjack.\n";
		resolveRound();
		return;
	}
}

void GameEngine::doTurn(Player* p, Hand& currentHand) {
	while (!currentHand.isFinished()) {
		printTurn(currentHand);
		
		if (currentHand.getRealValue() > 21) {
			std::cout << "---> BUSTED\n";
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
				currentHand.surrender();
				currentHand.finish();
				break;
		}
	}
}

/**
 *  Hands have finished, handle payouts.
 *  Players modify their own bankrolls for profit/loss.
*/
void GameEngine::resolveRound() {
	for (auto* p : players) {
		std::cout << p->getName() << " results\n";
		for (const Hand& h : p->hands) {
			std::cout << "Hand: ";
			h.printHand();

			if (h.isBusted()) {
				std::cout << "Lost " << h.getBet() << '\n';
				p->lose(h.getBet());
				continue;
			}
			if (dealerHand->isBusted()) {
				std::cout << "Win " << h.getBet() << '\n';
				p->win(h.getBet());
				continue;
			}
			
			// Natural blackjacks win
			if (dealerHand->isBlackjack() && !h.isBlackjack()) {
				std::cout << "Lost " << h.getBet() << '\n';
				p->lose(h.getBet());
				continue;
			} else if (!dealerHand->isBlackjack() && h.isBlackjack()) {
				p->win(h.getBet());
				std::cout << "Won " << h.getBet() << '\n';
				continue;
			}

			if (dealerHand->getRealValue() < h.getRealValue()) {
				p->win(h.getBet());
				std::cout << "Won " << h.getBet() << '\n';
			} else if (dealerHand->getRealValue() > h.getRealValue()) {
				p->lose(h.getBet());
				std::cout << "Lost " << h.getBet() << '\n';
			}
		}
	}
}
