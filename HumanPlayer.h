#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <string>

#include "Hand.h"
#include "Player.h"
#include "BlackjackRules.h"

class HumanPlayer : Player  {
public:
	HumanPlayer(std::string name);
	Action makeDecision(const Hand& currentHand, Card dealerUpCard, const BlackjackRules& rules);
};

#endif // !HUMANPLAYER_H
