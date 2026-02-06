#ifndef BLACKJACK_GAME
#define BLACKJACK_GAME

#include <vector>

enum CardType {
	ACE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
};

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
