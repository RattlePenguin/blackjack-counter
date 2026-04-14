#include "StrategyAdvisor.hpp"

Action StrategyAdvisor::getRecommendedAction(const Hand& playerHand, const Card& dealerUpCard, const BlackjackRules& rules) {
    int dealerValue = dealerUpCard.getValue();

    bool canDouble = playerHand.isTwoCards();
    bool canSplit = playerHand.isPair();
    bool canSurrender = rules.surrenderAllowed && playerHand.isTwoCards();

    if (canSplit) {
        Rank pairRank = playerHand.getCards().front().rank;
        Action splitAction = getPairAction(pairRank, dealerValue, rules);
        if (splitAction == Action::SPLIT) return Action::SPLIT;
    }

    if (playerHand.isSoft()) {
        return getSoftAction(playerHand.getRealValue(), dealerValue, rules, canDouble);
    } else {
        return getHardAction(playerHand.getRealValue(), dealerValue, rules, canDouble, canSurrender);
    }
}

std::string StrategyAdvisor::actionToString(Action action) {
    switch (action) {
        case Action::HIT: return "Hit";
        case Action::STAND: return "Stand";
        case Action::DOUBLE: return "Double";
        case Action::SPLIT: return "Split";
        case Action::SURRENDER: return "Surrender";
        default: return "Unknown";
    }
}
