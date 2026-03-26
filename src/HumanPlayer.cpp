#include "HumanPlayer.hpp"
#include <iostream>

HumanPlayer::HumanPlayer(std::string name) : Player(name) {}

/**
 *  Returns the HumanPlayer's Action depending on user input.
 *  Verifies whether or not action is valid.
 */
Action HumanPlayer::makeDecision(const Hand& currentHand, const BlackjackRules& rules) {
	bool isTwoCards { currentHand.isTwoCards() };
	bool isPair { currentHand.isPair() };
	
	while (true) {
		std::cout << "h: hit\n";
		std::cout << "s: stand\n";
		if (isTwoCards) std::cout << "d: double down\n";
		if (isPair) std::cout << "t: split\n";
		if (rules.surrenderAllowed && isTwoCards) std::cout << "y: surrender\n";

		std::string input {};
		if (!std::getline(std::cin >> std::ws, input)) {
			return Action::STAND;
		}

		if (input == "h" || input == "H") {
			return Action::HIT;
		} else if (input == "s" || input == "S") {
			return Action::STAND;
		} else if ((input == "d" || input == "D") && isTwoCards) {
			return Action::DOUBLE;
		} else if ((input == "t" || input == "T") && isPair) {
			return Action::SPLIT;
		} else if ((input == "y" || input == "Y") && isTwoCards) {
			return Action::SURRENDER;
		}
		std::cout << "Invalid Action!\n";
	}
}

