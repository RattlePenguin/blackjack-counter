#include <iostream>
#include <sstream>
#include <iomanip>

#include "GameEngine.hpp"
#include "StrategyAdvisor.hpp"

double parseBet(int runningCount, double decksRemaining);

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

int GameEngine::getRunningCount() const {
    return shoe.getSystemRunningCount();
}

double GameEngine::getTrueCount() const {
    double decks = shoe.getDecksRemaining();
    if (decks <= 0) return 0;
    return static_cast<double>(getRunningCount()) / decks;
}

void GameEngine::playRound() {
	// Shuffle shoe if necessary.
	if (shoe.needsShuffle()) {
		std::cout << "[Dealer] Shuffling the shoe...\n";
		shoe.shuffle();
	}

	startHands();

	std::cout << "----- HANDS -----\n";
	printHands();
	std::cout << '\n';
	if (dealerPreCheck()) {
		resolveRound();
		return;
	}
	
	bool allBusted { true };
	for (auto* p : players) {
		// Dynamic sizing to allow splitting
		for (size_t i = 0; i < p->hands.size(); ++i) {
			if (doTurn(p, i)) allBusted = false;
		}
	}

	if (!allBusted) {
		dealerTurn();
	}
	resolveRound();
}

void GameEngine::startHands() {
	dealerHand = new Hand(0); // Dealer has no bet
	
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < static_cast<int>(players.size()); ++j) {
			Player* p = players[j];

			if (i == 0) {
				if (j == 0) {
					p->startNewHand(parseBet(shoe.getSystemRunningCount(), shoe.getDecksRemaining()));
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
double parseBet(int runningCount, double decksRemaining) {
	double bet { -1 };
    std::string input;
    bool valid = false;

    double recommended = StrategyAdvisor::getRecommendedBet(runningCount, decksRemaining, 10.0);
    double trueCount = (decksRemaining > 0) ? static_cast<double>(runningCount) / decksRemaining : 0;

    while (!valid) {
		if (showCount) std::cout << "[COUNT] Running: " << runningCount << " | True: " << std::fixed << std::setprecision(2) << trueCount << "\n";
        if (showRecommendedBet) std::cout << "[HINT] Recommended Bet: $" << recommended << "\n";
		std::cout << "Enter your bet: ";
        if (!std::getline(std::cin >> std::ws, input)) {
			return 0.0;
		}

		std::cout << '\n';

        std::stringstream ss(input);
        if (ss >> bet) {
            // Check if there are any non-whitespace characters left in the stringstream
            // (e.g., if the user entered "123abc")
            char remaining;
            if (ss >> remaining) {
                std::cout << "Invalid input." << std::endl;
            } else {
                if (bet != recommended) {
                    std::cout << "[HINT] Actually, $" << recommended << " would be a better bet based on the count.\n";
                } else {
                    std::cout << "Correct bet size!\n";
                }
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
		std::cout << "[Dealer] Ace showing. Insurance? Y/N: (WIP)\n";
	}
	
	// Peek
	if (rules.lateSurrender && dealerHand->isBlackjack()) {
		std::cout << "Late surrender, [Dealer] shows Blackjack.\n";
		return true;
	}
	return false;
}

bool GameEngine::doTurn(Player* p, size_t handIndex) {
	std::cout << "--- " << p->getName() << " TURN ---\n";
	bool busted { false };
	while (!p->hands[handIndex].isFinished()) {
		Hand& currentHand = p->hands[handIndex];
		printTurn(currentHand);
		
		if (currentHand.getRealValue() > 21) {
			std::cout << "---> BUSTED\n";
			busted = true;

			p->lose(currentHand.getBet());
			std::cout << "Lost " << currentHand.getBet() << '\n';
			currentHand.zeroBet();
			currentHand.finish();
			break;
		}

		if (currentHand.isBlackjack()) {
			std::cout << "---> BLACKJACK!\n";
			currentHand.finish();
			break;
		}

		if (currentHand.isDoubled()) {
			currentHand.finish();
			break;
		}

		Action action { p->makeDecision(currentHand, dealerHand->getCards().front(), rules, shoe) };
		
		doAction(action, p, handIndex);
		std::cout << '\n';
	}
	return !busted;
}

void GameEngine::printTurn(Hand& hand) {
	std::cout << "[Dealer] Hand: ";
	dealerHand->printHand();
	std::cout << "Your Hand: ";
	hand.printHand();
}

void GameEngine::doAction(Action action, Player* p, size_t handIndex) {
	Hand& currentHand = p->hands[handIndex];
	switch (action) {
		case Action::HIT:
			std::cout << "---> HIT\n";
			currentHand.addCard(shoe.draw());
			break;
		case Action::STAND:
			std::cout << "---> STAND\n";
			printTurn(currentHand);
			currentHand.finish();
			break;
		case Action::DOUBLE:
			std::cout << "---> DOUBLE DOWN\n";
			currentHand.doubleDown();
			currentHand.addCard(shoe.draw());
			break;
		case Action::SPLIT: {
			std::cout << "---> SPLIT\n";
			double bet = currentHand.getBet();
			Hand& splitHand { p->startNewHand(bet) };
			
			// RE-ACQUIRE currentHand after startNewHand because of potential vector reallocation
			Hand& curHand { p->hands[handIndex] };
			
			Card splitCard { curHand.pop_back() };
			splitHand.addCard(splitCard);
			curHand.split();
			splitHand.split();
			
			// Hit each hand
			curHand.addCard(shoe.draw());
			splitHand.addCard(shoe.draw());
			
			// Split Aces get one card only.
			if (splitCard.rank == Rank::ACE) {
				printTurn(curHand);
				printTurn(splitHand);
				curHand.finish();
				splitHand.finish();
			}
			break;
		}
		case Action::SURRENDER:
			std::cout << "---> SURRENDER\n";
			currentHand.surrender();
			printTurn(currentHand);
			currentHand.finish();
			break;
	}
}

void GameEngine::dealerTurn() {
	std::cout << "--- [Dealer] TURN ---\n";

	dealerHand->getCards().back().faceDown = false;

	std::cout << "[Dealer] Hand: ";
	dealerHand->printHand();


	if (dealerHand->isBlackjack()) std::cout << "---> [Dealer] BLACKJACK!\n";

	while (dealerShouldHit()) {
		std::cout << "---> [Dealer] HITS\n";
		dealerHand->addCard(shoe.draw());
		dealerHand->printHand();
		std::cout << '\n';
	}

	if (dealerHand->is21()) std::cout << "---> [Dealer] GOT 21!\n";

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

			if (h.isBusted()) continue;

			if (h.isSurrendered()) {
				std::cout << "Surrendered" << h.getBet() << '\n';
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
			} else {
				std::cout << "Push, " << h.getBet() << " returned\n";
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
