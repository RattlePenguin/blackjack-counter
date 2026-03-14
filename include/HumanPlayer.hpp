#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <string>

#include "Hand.hpp"
#include "Player.hpp"
#include "BlackjackRules.hpp"

class HumanPlayer : public Player  {
public:
	HumanPlayer(std::string name);
	Action makeDecision(const Hand& currentHand, const BlackjackRules& rules);
};

#endif // !HUMANPLAYER_H
