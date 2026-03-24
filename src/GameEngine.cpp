#include <iostream>
#include <sstream>

#include "GameEngine.hpp"

double parseBet();

GameEngine::GameEngine(int numDecks, double penetration, unsigned int seed)
	: shoe(numDecks, penetration, seed)
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
	printHands();
	std::cout << '\n';
	if (dealerPreCheck()) {
		resolveRound();
		return;
	}

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
					p->startNewHand(parseBet());
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
double parseBet() {
	double bet { -1 };
    std::string input;
    bool valid = false;
    while (!valid) {
		std::cout << "Enter your bet: ";
        std::getline(std::cin >> std::ws, input);

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

void GameEngine::printHands() {
	std::cout << "[Dealer] Hand: ";
	dealerHand->printHand();
	for (auto* p : players) {
		std::cout << p->getName() << " Hands: ";
		for (const auto& h : p->hands) h.printHand();
	}
}

bool GameEngine::dealerPreCheck() {
	if (dealerHand->getCards().front().rank == Rank::ACE) {
		std::cout << "[Dealer] Ace showing. Insurance? Y/N: ";
	}
	
	// Peek
	if (rules.lateSurrender && dealerHand->isBlackjack()) {
		std::cout << "Late surrender, [Dealer] shows Blackjack.\n";
		return true;
	}
	return false;
}

void GameEngine::doTurn(Player* p, Hand& currentHand) {
	std::cout << "--- " << p->getName() << " TURN ---\n";
	while (!currentHand.isFinished()) {
		printTurn(currentHand);
		
		if (currentHand.getRealValue() > 21) {
			std::cout << "---> BUSTED\n\n";
			currentHand.finish(); // TODO Bet should be collected here
			break;
		}

		if (currentHand.isBlackjack()) {
			std::cout << "---> BLACKJACK!\n\n";
			currentHand.finish(); // TODO Bet should be paid out here 3:2 odds
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
		std::cout << '\n';
	}
}

void GameEngine::printTurn(Hand& hand) {
	std::cout << "[Dealer] Hand: ";
	dealerHand->printHand();
	std::cout << "Your Hand: ";
	hand.printHand();
}

void GameEngine::dealerTurn() {
	std::cout << "--- [Dealer] TURN ---\n";

	dealerHand->getCards().back().faceDown = false;

	std::cout << "[Dealer] Hand: ";
	dealerHand->printHand();

	while (dealerShouldHit()) {
		std::cout << "---> [Dealer] HITS\n";
		dealerHand->addCard(shoe.draw());
		dealerHand->printHand();
		std::cout << '\n';
	}

	if (dealerHand->isBusted()) {
		std::cout << "---> [Dealer] BUSTED\n";
	} else {
		std::cout << "---> [Dealer] STANDS\n";
	}
}

/**
 *  Hands have finished, handle post game.
 *  Clears hands at the end.
*/
void GameEngine::resolveRound() {
	for (auto* p : players) {
		std::cout << "---> " << p->getName() << " results\n";
		for (const Hand& h : p->hands) {
			std::cout << "Hand: ";
			h.printHand();

			if (h.isSurrendered() || h.isBusted()) {
				std::cout << "Lost " << h.getBet() << '\n';
				p->lose(h.getBet());
				continue;
			}

			// Natural blackjacks win
			if (dealerHand->isBlackjack() && !h.isBlackjack()) {
				std::cout << "Lost " << h.getBet() << '\n';
				p->lose(h.getBet());
				continue;
			} else if (!dealerHand->isBlackjack() && h.isBlackjack()) {
				std::cout << "Won " << h.getBet() * rules.blackjackPayout << '\n';
				p->win(h.getBet() * rules.blackjackPayout);
				continue;
			}

			if (dealerHand->isBusted()) {
				std::cout << "Won " << h.getBet() << '\n';
				p->win(h.getBet());
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
	clearHands();
}

void GameEngine::clearHands() {
	delete dealerHand;
	dealerHand = nullptr;

	for (auto* p : players) {
		p->clearHands();
	}
}
