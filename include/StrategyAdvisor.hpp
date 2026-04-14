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
    static Action getRecommendedAction(const Hand& playerHand, const Card& dealerUpCard, const BlackjackRules& rules);
    static std::string actionToString(Action action);

private:
    static Action getHardAction(int value, int dealerValue, const BlackjackRules& rules, bool canDouble, bool canSurrender);
    static Action getSoftAction(int value, int dealerValue, const BlackjackRules& rules, bool canDouble);
    static Action getPairAction(Rank pairRank, int dealerValue, const BlackjackRules& rules);
};

#endif // STRATEGYADVISOR_H
