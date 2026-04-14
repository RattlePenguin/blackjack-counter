#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <string>

#include "Hand.hpp"
#include "Player.hpp"
#include "BlackjackRules.hpp"
#include "StrategyAdvisor.hpp"
#include <vector>

class HumanPlayer : public Player  {
public:
	HumanPlayer(std::string name);
	Action makeDecision(const Hand& currentHand, const Card& dealerUpCard, const BlackjackRules& rules) override;
	
	void setHints(bool show);
	bool getHints() const;
	void printStrategySummary() const;
	void clearStrategyRecords();

private:
	bool showHints { false };
	std::vector<StrategyRecord> strategyRecords {};
};

#endif // !HUMANPLAYER_H
