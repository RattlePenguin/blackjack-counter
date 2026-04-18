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

double StrategyAdvisor::getRecommendedBet(int runningCount, double decksRemaining, double unitBet) {
    if (decksRemaining <= 0) return unitBet;
    
    double trueCount = static_cast<double>(runningCount) / decksRemaining;
    
    if (trueCount <= 1.0) return unitBet;
    if (trueCount < 2.0) return unitBet; 
    if (trueCount < 3.0) return unitBet * 2;
    if (trueCount < 4.0) return unitBet * 4;
    if (trueCount < 5.0) return unitBet * 8;
    return unitBet * 12;
}

Action StrategyAdvisor::getHardAction(int value, int dealerValue, const BlackjackRules& rules, bool canDouble, bool canSurrender) {
    if (canSurrender) {
        if (value == 16 && (dealerValue >= 9)) return Action::SURRENDER;
        if (value == 15 && dealerValue == 10) return Action::SURRENDER;
        if (value == 15 && rules.hitSoft17 && dealerValue == 11) return Action::SURRENDER;
    }

    if (value >= 17) return Action::STAND;
    if (value >= 13 && value <= 16) {
        if (dealerValue <= 6) return Action::STAND;
        return Action::HIT;
    }
    if (value == 12) {
        if (dealerValue >= 4 && dealerValue <= 6) return Action::STAND;
        return Action::HIT;
    }
    if (value == 11) {
        if (canDouble) {
            if (dealerValue == 11 && !rules.hitSoft17) return Action::HIT;
            return Action::DOUBLE;
        }
        return Action::HIT;
    }
    if (value == 10) {
        if (canDouble && dealerValue <= 9) return Action::DOUBLE;
        return Action::HIT;
    }
    if (value == 9) {
        if (canDouble && dealerValue >= 3 && dealerValue <= 6) return Action::DOUBLE;
        return Action::HIT;
    }
    return Action::HIT;
}

Action StrategyAdvisor::getSoftAction(int value, int dealerValue, const BlackjackRules& rules, bool canDouble) {
    switch (value) {
        case 20: // A,9
        case 21:
            return Action::STAND;
        case 19: // A,8
            if (canDouble && rules.hitSoft17 && dealerValue == 6) return Action::DOUBLE;
            return Action::STAND;
        case 18: // A,7
            if (dealerValue >= 9) return Action::HIT;
            if (canDouble && dealerValue >= 3 && dealerValue <= 6) return Action::DOUBLE;
            return Action::STAND;
        case 17: // A,6
            if (canDouble && dealerValue >= 3 && dealerValue <= 6) return Action::DOUBLE;
            return Action::HIT;
        case 16: // A,5
        case 15: // A,4
            if (canDouble && dealerValue >= 4 && dealerValue <= 6) return Action::DOUBLE;
            return Action::HIT;
        case 14: // A,3
        case 13: // A,2
            if (canDouble && (dealerValue == 5 || dealerValue == 6)) return Action::DOUBLE;
            return Action::HIT;
        default:
            return Action::HIT;
    }
}

Action StrategyAdvisor::getPairAction(Rank pairRank, int dealerValue, const BlackjackRules& rules) {
    switch (pairRank) {
        case Rank::ACE:
        case Rank::EIGHT:
            return Action::SPLIT;
        case Rank::TEN:
        case Rank::JACK:
        case Rank::QUEEN:
        case Rank::KING:
            return Action::STAND;
        case Rank::NINE:
            if (dealerValue == 7 || dealerValue == 10 || dealerValue == 11) return Action::STAND;
            return Action::SPLIT;
        case Rank::SEVEN:
            if (dealerValue <= 7) return Action::SPLIT;
            return Action::HIT;
        case Rank::SIX:
            if (dealerValue <= 6) return Action::SPLIT;
            return Action::HIT;
        case Rank::FIVE:
            if (dealerValue <= 9) return Action::DOUBLE;
            return Action::HIT;
        case Rank::FOUR:
            if (rules.doubleAfterSplit && (dealerValue == 5 || dealerValue == 6)) return Action::SPLIT;
            return Action::HIT;
        case Rank::THREE:
        case Rank::TWO:
            if (dealerValue <= 7) return Action::SPLIT;
            return Action::HIT;
        default:
            return Action::HIT;
    }
}
