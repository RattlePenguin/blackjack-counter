#include "HumanPlayer.hpp"
#include <iostream>
#include <iomanip>

HumanPlayer::HumanPlayer(std::string name) : Player(name) {}

/**
 *  Returns the HumanPlayer's Action depending on user input.
 *  Verifies whether or not action is valid.
 */
Action HumanPlayer::makeDecision(const Hand& currentHand, const Card& dealerUpCard, const BlackjackRules& rules) {
	bool isTwoCards { currentHand.isTwoCards() };
	bool isPair { currentHand.isPair() };

    Action recommended = StrategyAdvisor::getRecommendedAction(currentHand, dealerUpCard, rules);

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

        Action chosen;
		if (input == "h" || input == "H") {
			chosen = Action::HIT;
		} else if (input == "s" || input == "S") {
			chosen = Action::STAND;
		} else if ((input == "d" || input == "D") && isTwoCards) {
			chosen = Action::DOUBLE;
		} else if ((input == "t" || input == "T") && isPair) {
			chosen = Action::SPLIT;
		} else if ((input == "y" || input == "Y") && isTwoCards) {
			chosen = Action::SURRENDER;
		} else {
            std::cout << "Invalid Action!\n";
            continue;
        }

        // Track strategy
        strategyRecords.push_back({
            currentHand.getRealValue(),
            currentHand.isSoft(),
            currentHand.isPair(),
            dealerUpCard,
            chosen,
            recommended,
            chosen == recommended
        });

        if (showHints) {
            if (chosen != recommended) {
                std::cout << "Actually, " << StrategyAdvisor::actionToString(recommended) << " would have been better.\n";
            } else {
                std::cout << "Correct move!\n";
            }
        }

        return chosen;
	}
}

void HumanPlayer::setHints(bool show) { showHints = show; }
bool HumanPlayer::getHints() const { return showHints; }

void HumanPlayer::printStrategySummary() const {
    if (strategyRecords.empty()) {
        std::cout << "No decisions made yet.\n";
        return;
    }

    std::cout << "\n--- STRATEGY SUMMARY ---\n";
    std::cout << std::left << std::setw(15) << "Player" << std::setw(10) << "Dealer" << std::setw(12) << "Your Move" << std::setw(12) << "Correct" << "Result\n";
    std::cout << "------------------------------------------------------------\n";

    int correctCount = 0;
    for (const auto& record : strategyRecords) {
        std::string pStr = std::to_string(record.playerValue);
        if (record.isSoft) pStr = "Soft " + pStr;
        if (record.isPair && record.playerValue != 20) pStr = "Pair of " + std::to_string(record.playerValue / 2); // Simple pair display

        std::string dStr = std::to_string(record.dealerUpCard.getValue());
        if (record.dealerUpCard.rank == Rank::ACE) dStr = "Ace";

        std::cout << std::left << std::setw(15) << pStr 
                  << std::setw(10) << dStr 
                  << std::setw(12) << StrategyAdvisor::actionToString(record.actualAction)
                  << std::setw(12) << StrategyAdvisor::actionToString(record.correctAction)
                  << (record.correct ? "CORRECT" : "WRONG") << "\n";

        if (record.correct) correctCount++;
    }

    double accuracy = (static_cast<double>(correctCount) / strategyRecords.size()) * 100.0;
    std::cout << "------------------------------------------------------------\n";
    std::cout << "Overall Accuracy: " << std::fixed << std::setprecision(1) << accuracy << "%\n";
}

void HumanPlayer::clearStrategyRecords() { strategyRecords.clear(); }
