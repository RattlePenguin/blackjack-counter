#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(std::string name) : Player(name) {}

HumanPlayer::Action makeDecision(const Hand& currentHand, Card dealerUpCard, const BlackjackRules& rules);

