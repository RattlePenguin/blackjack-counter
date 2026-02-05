#ifndef BLACKJACK_GAME
#define BLACKJACK_GAME

#include <vector>

class BlackjackGame {
private:
	std::vector<int> cards {}; // Acts as the entire collective deck.

public:
	/**
	 *  Fill the cards member var with numDecks amount of deck cards.
	 */
	void fillCards(int numDecks);
};

#endif
