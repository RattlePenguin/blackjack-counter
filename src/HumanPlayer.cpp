#include "HumanPlayer.hpp"
#include <iostream>

HumanPlayer::HumanPlayer(std::string name) : Player(name) {}

/**
 *  Returns the HumanPlayer's Action depending on user input.
 *  Verifies whether or not action is valid.
 */
Action HumanPlayer::makeDecision(const Hand& currentHand, Card dealerUpCard, const BlackjackRules& rules) {
	bool isTwoCards { currentHand.isTwoCards() };
	bool isPair { currentHand.isPair() };
	
	while (true) {
		std::cout << "h: hit\n";
		std::cout << "s: stand\n";
		if (isTwoCards) std::cout << "d: double down\n";
		if (isPair) std::cout << "t: split\n";
		if (rules.surrenderAllowed && isTwoCards) std::cout << "y: surrender\n";

		std::string input {};
		std::cin >> input;
		if (input == "h") {
			return Action::HIT;
		} else if (input == "s") {
			return Action::STAND;
		} else if (input == "d" && isTwoCards) {
			return Action::DOUBLE;
		} else if (input == "t" && isPair) {
			return Action::SPLIT;
		} else if (input == "y" && isTwoCards) {
			return Action::SURRENDER;
		}
		std::cout << "Invalid Action!\n";
	}
}

