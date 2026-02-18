#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameEngine {
public:
	GameEngine(int numDecks);
private:
	Shoe shoe;
	BlackjackRules rules {};
	std::vector<Player&> players {};
	Hand& dealerHand;

	bool dealerShouldHit();
	void addPlayer(Player player);
	void playRound();
	void resolveRound();
};

#endif // !GAMEENGINE_H
