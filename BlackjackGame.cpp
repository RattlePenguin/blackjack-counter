#include <iostream>
#include <vector>

const int DECK_SIZE { 52 };

class BlackjackGame {
private:
	std::vector<int> cards {}; // Acts as the entire collective deck.

public:
	/**
	 *  Fill the cards member var with numDecks amount of deck cards.
	 */
	void fillCards(int numDecks) {
		for (int i = 0; i < numDecks; ++i) {
			for (int j = 0; j < DECK_SIZE; ++j) {
				cards.emplace_back(j);
			}
		}
	}

};
