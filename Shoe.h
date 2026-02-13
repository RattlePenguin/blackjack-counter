#include <vector>

#include "Card.h"

class Shoe {
public:
	Shoe(int totalDecks, double penetration);
	void initialise();
	void shuffle();
	Card draw();

private:
	std::vector<Card> cards {};
	int totalDecks {};
	int cardsDealtIndex {};
	int cutCardIndex {};
};
