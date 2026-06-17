#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <string>

#include "Hand.hpp"
#include "Player.hpp"
#include "BlackjackRules.hpp"
#include "StrategyAdvisor.hpp"
#include "Shoe.hpp"
#include <vector>

class HumanPlayer : public Player  {
public:
	HumanPlayer(std::string name);
	Action makeDecision(const Hand& currentHand, const Card& dealerUpCard, const BlackjackRules& rules, const Shoe& shoe) override;
	
	void setStrategyHints(bool show);
	bool getStrategyHints() const;
	void setCountingHints(bool show);
	bool getCountingHints() const;
	void printStrategySummary() const;
	void clearStrategyRecords();

private:
	bool showStrategyHints { false };
	bool showCountingHints { false };
	std::vector<StrategyRecord> strategyRecords {};
};

#endif // !HUMANPLAYER_H
