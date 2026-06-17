#include "HumanPlayer.hpp"
#include <iostream>
#include <iomanip>

HumanPlayer::HumanPlayer(std::string name) : Player(name) {}

/**
 *  Returns the HumanPlayer's Action depending on user input.
 *  Verifies whether or not action is valid.
 */
Action HumanPlayer::makeDecision(const Hand& currentHand, const Card& dealerUpCard, const BlackjackRules& rules, const Shoe& shoe) {
	bool isTwoCards { currentHand.isTwoCards() };
	bool isPair { currentHand.isPair() };

    Action recommendedAction = StrategyAdvisor::getRecommendedAction(currentHand, dealerUpCard, rules);

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

        Action chosenAction;
		if (input == "h" || input == "H") {
			chosenAction = Action::HIT;
		} else if (input == "s" || input == "S") {
			chosenAction = Action::STAND;
		} else if ((input == "d" || input == "D") && isTwoCards) {
			chosenAction = Action::DOUBLE;
		} else if ((input == "t" || input == "T") && isPair) {
			chosenAction = Action::SPLIT;
		} else if ((input == "y" || input == "Y") && isTwoCards) {
			chosenAction = Action::SURRENDER;
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
            chosenAction,
            recommendedAction,
            chosenAction == recommendedAction
        });

        if (showStrategyHints) {
            if (chosenAction != recommendedAction) {
                std::cout << "Actually, " << StrategyAdvisor::actionToString(recommendedAction) << " would have been better.\n";
            } else {
                std::cout << "Correct move!\n";
            }
        }

		if (showCountingHints) {

			double recommendedBet = StrategyAdvisor::getRecommendedBet(runningCount, decksRemaining, 10.0);
			double trueCount = (decksRemaining > 0) ? static_cast<double>(runningCount) / decksRemaining : 0;
		}

        return chosen;
	}
}

void HumanPlayer::setStrategyHints(bool show) { showStrategyHints = show; }
bool HumanPlayer::getStrategyHints() const { return showStrategyHints; }
void HumanPlayer::setCountingHints(bool show) { showCountingHints = show; }
bool HumanPlayer::getCountingHints() const { return showCountingHints; }

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
