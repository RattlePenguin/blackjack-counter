#ifndef STRATEGYADVISOR_H
#define STRATEGYADVISOR_H

#include <string>
#include <vector>
#include "Hand.hpp"
#include "BlackjackRules.hpp"

struct StrategyRecord {
    int playerValue;
    bool isSoft;
    bool isPair;
    Card dealerUpCard;
    Action actualAction;
    Action correctAction;
    bool correct;
};

class StrategyAdvisor {
public:
	/**
	 *  Returns the recommended action given the current hand and rules.
	 */
    static Action getRecommendedAction(const Hand& playerHand, const Card& dealerUpCard, const BlackjackRules& rules);

	/**
	 *  Returns the given action as a string.
	 */
    static std::string actionToString(Action action);

private:
	/**
	 *  Returns the recommended action given the player's current hand as a hard value.
	 *  Compares against dealer value.
	 *  Recommended action can vary depending on rules.
	 */
    static Action getHardAction(int value, int dealerValue, const BlackjackRules& rules, bool canDouble, bool canSurrender);
	
	/**
	 *  Returns the recommended action given the player's current hand as a soft value.
	 */
    static Action getSoftAction(int value, int dealerValue, const BlackjackRules& rules, bool canDouble);

	/**
	 *  Returns the recommended action given the player's current hand as a pair.
	 */
    static Action getPairAction(Rank pairRank, int dealerValue, const BlackjackRules& rules);
};

#endif // STRATEGYADVISOR_H
